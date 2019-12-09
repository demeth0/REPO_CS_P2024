//Programme qui fait clignoter une LED indéfiniment

int nombreDeFois; // variable pour le nombre de fois
int numeroPin; // variable pour le pin utilisé
boolean faireCode; // variable pour arrêter le clignotement

void setup()
{
    numeroPin=13; // initialisation pin à 13
    pinMode(numeroPin,OUTPUT);
    nombreDeFois=10; // initialisation nb de fois à 10
    faireCode=true; // initialisation à true
}

void loop()
{
    if (faireCode) // test si true
    {
        for (int t=0;t<nombreDeFois;t=t+1) // boucle clignotement
        {
            //allume
            digitalWrite(numeroPin,HIGH);
            delay (250);
            //éteint
            digitalWrite(numeroPin,LOW);
            delay (250);
        }
        faireCode=false;
    }
}
