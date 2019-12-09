boolean etat;

void setup()
{
    Serial.begin(9600);
    etat=true;
}
void loop()
{
    etat=3<5;
    Serial.println(etat);
}
