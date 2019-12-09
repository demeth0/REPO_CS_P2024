//Compte jusqu'à 20
int compteur;
void setup() {
  Serial.begin(9600);
  Serial.println("*** Debut du programme ***");
  compteur=1;
}

void loop() {
  if (compteur <= 20)
  {
  Serial.println(compteur);
  compteur=compteur+1;
  }
}
