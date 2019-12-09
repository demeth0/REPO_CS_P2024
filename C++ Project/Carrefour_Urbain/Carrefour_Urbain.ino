/*
Programe qui modélise un carrefour en allumant les feux piétons et voitures alternativement,
et qui capte le passage de bus via des capteurs magnétiques (il passe les feux au vert pour les bus)
-Version cathode commune (anode commune : !bitRead)
*/

//Variables de boucles
boolean erreur=false;
boolean route=false;
boolean demandePriseEnCompte=false;
float temps=0;

//Pins de sortie (LED RGB)de feux voitures en sortie sur les pins 1, 2, 3 et 4, en alternant logiciellement à chaque tour de la boucle
byte PIN_LED_Rv1=1+route;
byte PIN_LED_Rv2=1+!route;
byte PIN_LED_Vv1=3+route;
byte PIN_LED_Vv2=3+!route;

//Pins de sortie (LED RGB)de feux piétons en sortie sur les pins 6, 7, 8, et 9 en alternant logiciellement à chaque tour de la boucle (les broches bleues ne sont pas branchées car inutiles)
byte PIN_LED_Rp1=6+route;
byte PIN_LED_Rp2=6+!route;
byte PIN_LED_Vp1=8+route;
byte PIN_LED_Vp2=8+!route;

//Pins d'entrées (Capteurs magnétiques) sur les pins 16 et 17
const byte CAPTEUR_HALL_1=16+route;
const byte CAPTEUR_HALL_2=16+!route;

//Pins d'entrées (Boutons) sur les pins 19, 20 et 21
const byte BOUTON1=19+route;
const byte BOUTON2=19+!route;
const byte BOUTON_ARRET=21;

//Couleurs utilisées
const byte COULEUR_VERTE=0b010;
const byte COULEUR_ROUGE=0b100;
const byte COULEUR_JAUNE=0b110;
const byte COULEUR_NOIRE=0b000;

//Définie une couleur pour chaque broche de la LED RGB piéton 1
void displayColorPieton1 (byte couleur) {

  digitalWrite(PIN_LED_Rp1, bitRead(couleur, 2));
  digitalWrite(PIN_LED_Vp1, bitRead(couleur, 1));
}

//Définie une couleur pour chaque broche de la LED RGB Piéton 2
void displayColorPieton2 (byte couleur) {
  // Version anode commune (pour cathode commune : bitRead)
  digitalWrite(PIN_LED_Rp2, bitRead(couleur, 2));
  digitalWrite(PIN_LED_Vp2, bitRead(couleur, 1));
}

//Définie une couleur pour chaque broche de la LED RGB Voiture 1
void displayColorVoiture1 (byte couleur) {
  // Version cathode commune (pour anode commune : !bitRead)
  digitalWrite(PIN_LED_Rv1, bitRead(couleur, 2));
  digitalWrite(PIN_LED_Vv1, bitRead(couleur, 1));
}

//Définie une couleur pour chaque broche de la LED RGB Voiture 2
void displayColorVoiture2 (byte couleur) {
  // Version cathode commune (pour anode commune : !bitRead)
  digitalWrite(PIN_LED_Rv2, bitRead(couleur, 2));
  digitalWrite(PIN_LED_Vv2, bitRead(couleur, 1));
}

//Inclus le fichier suivant
#include <avr/wdt.h>

//Fonction de reset de la carte
void software_Reboot()
{
  //Active la fonction watchdog qui reset la carte après 15ms d'inactivité
  wdt_enable(WDTO_15MS);
  //Boucle infinie sans aucune action qui va obliger le reset de la carte
  while(1){}
}

void setup() {
  //Initialise la communication avec l'ordinateur
  Serial.begin(9600);

  //Pins de sorties (LED RGB Voitures)
  pinMode(PIN_LED_Rv1,OUTPUT);
  pinMode(PIN_LED_Vv1,OUTPUT);
  pinMode(PIN_LED_Rv2,OUTPUT);
  pinMode(PIN_LED_Vv2,OUTPUT);

  //Pins de sorties (LED RG Piétons)
  pinMode(PIN_LED_Rp1,OUTPUT);
  pinMode(PIN_LED_Vp1,OUTPUT);
  pinMode(PIN_LED_Rp2,OUTPUT);
  pinMode(PIN_LED_Vp2,OUTPUT);

  //Pins d'entrées (Capteurs magnétiques)
  pinMode(CAPTEUR_HALL_1,INPUT);
  pinMode(CAPTEUR_HALL_2,INPUT);

  //Pins d'entrées (Boutons)
  pinMode(BOUTON1,INPUT_PULLUP);
  pinMode(BOUTON2,INPUT_PULLUP);
  pinMode(BOUTON_ARRET,INPUT_PULLUP);
}

void loop() {
  //Passe les feux piétons anciennement verts au rouge
  displayColorPieton1(COULEUR_ROUGE);
  //Passe les feux voitures anciennement verts au orange
  displayColorVoiture1(COULEUR_JAUNE);
  //Attend 1 seconde
  delay(1000);
  //Passe les feux voitures anciennement oranges au rouge
  displayColorVoiture1(COULEUR_ROUGE);
  //Test que l'opération s'est bien déroulée
  if(digitalRead(PIN_LED_Rv1)==1 \
  && digitalRead(PIN_LED_Vv1)==0 \
  && digitalRead(PIN_LED_Rp1)==1 \
  && digitalRead(PIN_LED_Vp1)==0){
    //Passe les feux piétons anciennement rouges au vert
    displayColorPieton2(COULEUR_VERTE);
    //Passe les feux voitures anciennement rouges au vert
    displayColorVoiture2(COULEUR_VERTE);
    //Test que l'opération s'est bien déroulée
    if(digitalRead(PIN_LED_Rv2)==0 \
    && digitalRead(PIN_LED_Vv2)==1 \
    && digitalRead(PIN_LED_Rp2)==0 \
    && digitalRead(PIN_LED_Vv2)==1){
      //Boucle d'attente de 20 secondes entre deux changements de feux
      while(temps<=20){
        //Attend 0.1 seconde
        delay(100);
        //Test si le bouton piéton de la route rouge a été activé
        if(digitalRead(BOUTON2)==1 && !demandePriseEnCompte){
          //Reduit de 5 secondes l'attente restante
          temps=temps+5;
          Serial.println("Temps restant réduis de 5 secondes");
          //Active la variable de demande prise en compte empêchant de retourner dans ce test
          demandePriseEnCompte=true;
        }
        //Test si le capteur de bus de la voie verte a été activé
        if(digitalRead(CAPTEUR_HALL_1)==1){
          //Test si le temps restant est strictement inférieur à 2 secondes
          if(temps>18){
            Serial.println("Temps restant inférieur à 2 secondes, attente de 2 secondes puis sortie de la boucle");
            //Attend 2 secondes
            delay(2000);
            //Réduit le temps d'attente restant à 0 secondes
            temps=20;
          }
          Serial.println("Temps restant supérieur à 2 secondes, aucune action nécessaire");
        }
        //Test si le capteur de bus de la voie rouge a été activé
        if(digitalRead(CAPTEUR_HALL_2)==1){
          Serial.println("Sortie de la boucle");
          //Réduit le temps d'attente restant à 0 secondes
          temps=20;
        }
        //Réduit le temps d'attente restant de 0.1 secondes
        temps=temps+0.1;
      }
    }else{
      //Définit la variable d'entrée dans la boucle d'erreur à vrai
      erreur=true;
    }
  }else{
    //Définir la variable d'entrée dans la boucle d'erreur à vrai
    erreur=true;
  }
  //Test si la variable d'entrée dans la boucle d'erreur a été définie en tant que vrai
  if(erreur){
    //Envoie un message d'erreur sur la console
    Serial.println("PROBLEME DE FONCTIONNEMENT DES FEUX, ACTIVATION DU MODE ERREUR, ACTION OPERATEUR REQUISE");
    //Eteint tous les feux piétons
    displayColorPieton1(COULEUR_NOIRE);
    displayColorPieton2(COULEUR_NOIRE);
    //Boucle de clignotement des feux voitures
    while(erreur){
      //Met les feux voitures à l'orange
      displayColorVoiture1(COULEUR_JAUNE);
      displayColorVoiture2(COULEUR_JAUNE);
      //Attend 0.5 secondes
      delay(500);
      //Eteint les feux voitures
      displayColorVoiture1(COULEUR_NOIRE);
      displayColorVoiture2(COULEUR_NOIRE);
      //Attend 0.5 secondes
      delay(500);
      //Test si le bouton d'arrêt a été activé
      if(digitalRead(BOUTON_ARRET)==1){
        //Active la fonction de reset du système
        software_Reboot();
      }
    }
  }
  //Inverse la valeur de la variable route
  route=!route;
}
