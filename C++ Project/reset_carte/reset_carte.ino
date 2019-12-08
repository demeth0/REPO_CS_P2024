//Programme qui permet de reboot une carte

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

//Appelle la fonction éponyme
software_Reboot();
