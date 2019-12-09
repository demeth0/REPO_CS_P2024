//Gestion de l'incrementation en Arduino
int compteur; //déclaration d'une variable compteur

void setup()
{
    Serial.begin(9600); //initialisation communication
    compteur=1; // initialisation de compteur
}

void loop()
{
    Serial.println(compteur); //affiche la valeur de compteur
    compteur=compteur+1; //on ajoute 1 à compteur
}
