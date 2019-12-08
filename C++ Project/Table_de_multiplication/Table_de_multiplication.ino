int nombreAMultiplier;
int incrementation;
int resultat;
void setup() {
  nombreAMultiplier = 7;
  Serial.println("***********************");
  Serial.println("Table de multiplication");
  Serial.println("La table de : " + nombreAMultiplier);
  Serial.println();
  for (incrementation = 0; incrementation <= 14; incrementation++) {
    resultat = nombreAMultiplier * incrementation;
    Serial.println(incrementation + " * " + nombreAMultiplier " = " + resultat);
  }
  Serial.println();
  Serial.println("***********************");
}

void loop() {
  // put your main code here, to run repeatedly:

}
