//Gestion de l'allumage de LED en Arduino
const int CONNEXION=13;
void setup()
{
    pinMode(CONNEXION,OUTPUT);  //Signale à l’Arduino que la connexion 13 doit pouvoir envoyer du courant
    }

void loop()
{
    digitalWrite(CONNEXION,HIGH);
    delay(1000);
    digitalWrite(CONNEXION,LOW);
    delay(1000);
}
