//Gestion des conditions en arduino :
int affichageEffectue;// déclaration de la variable

void setup()
{
    Serial.begin(9600);
    affichageEffectue=0;//initialisation de la variable
}

void loop()
{
    if (affichageEffectue==0)
    {
        //ce code n'est exécuté que si la condition est vérifiée
        Serial.println("Hello");
        Serial.println("Arduino");
        Serial.println("World !");
        affichageEffectue=1;//on passe la variable à 1 pour ne plus exécuter le code
    }
}
