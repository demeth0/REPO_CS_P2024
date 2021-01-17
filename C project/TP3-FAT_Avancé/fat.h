#define BLOCSIZE 32 //512
#define BLOCNUM 10 //1024
#define NAMELEN 25 //256
#define DEFAULT_PARTITION "FAT_partition.img"

struct objet
{
char nom[NAMELEN];
unsigned int taille;
unsigned short auteur;
unsigned short index;
struct objet *next;
};

struct objet *obj  ;
char volume[BLOCSIZE * BLOCNUM ];
unsigned short FAT[BLOCNUM];
unsigned short freeblocks;


/**
\brief Cette fonction permet :
D'initialiser le tableau FAT en déclarant tous les blocs libres.
D'initialiser la variable freeblocks à BLOCNUM.
D'initialiser la variable obj
*/
void initialise_fat();

/**
\brief Cette fonction permet de rechercher un objet par son nom dans la liste chaînée décrivant les objets
\param nom nom de l'objet à rechercher 
\return pointeur vers l'objet trouvé ou NULL sinon.
*/
struct objet *rechercher_objet(char *nom);

/** 
\brief Cette fonction permet de créer un objet en vérifiant qu'aucun objet n'a le même nom dans la liste (pas triée par nom)
si possible, de réserver des blocs dans le tableau FAT et de copier les données (data) dans ces blocs.
mettre à jour la variable freeblocks 
\param nom nom de l'objet 
\param auteur proprietaire de l'objet 
\param taille la taille de l'objet 
\param data les données à copier
*/
struct objet *creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data);

/**
\brief  Cette fonction permet de supprimer un objet trouvé par son nom, de libérer les blocs dans le tableau FAT, et de mettre à jour la variable freeblocks 
\param nom 
\return -1 si erreur, 0 sinon.
*/
int supprimer_objet(char *nom);


/** 
\brief Cette fonction permet :
De supprimer l'ensemble des objets
De liberer l'ensemble des blocs dans le tableau FAT
De modifier la variable freeblocks
*/
void supprimer_tout();

/** POUR LES PLUS RAPIDES ..................** BONUS ** BONUS ** BONUS ** 
\brief Cette fonction permet :
De lire le contenu d'un objet et de le copier dans une structure de données allouée dynamiquement 
Attention à la taille !!!!!!!!!!!!!!
\param nom nom de l'objet
\return -1 si erreur, 0 sinon.
*/

int lire_objet(struct objet *o,char **data);

