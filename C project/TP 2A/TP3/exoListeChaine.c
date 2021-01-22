#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Ici, on est oblig� d'utiliser la notation struct xxx,
car la structure s'auto-r�f�rence!*/
typedef struct node {
	char data ;
	struct node *link ;
} Lnode ;

/*
Description:
	cr��er une node et retourne un pointeur vers cette nouvelle node
parameter:
	node: node suivante
	item: contenue de la node
return:
	pointeur vers la node cr��e
*/
Lnode *CreerNode(Lnode *node,char item){
	//alloue la memoire
	Lnode *element = malloc(sizeof(Lnode));

	//v�rifie si l'allocation de m�moire a r�ussie
	if(element == NULL)
    {
        fprintf(stderr, "l'allocation dynamique a �chou�e\n");
        exit(EXIT_FAILURE);
    }

    //remplis la node avec ses parametres
    element->data=item;
    element->link = node;
    return element;
}

/* Insertion en "t�te de liste" */
void insertionTete(Lnode **ph,char item){
    Lnode *new_element = CreerNode(*ph,item);
    *ph = new_element;
}

/* Insertion en "queue de liste" */
void insertionQueue(Lnode **ph,char item)    {
	Lnode *element = (*ph);
	Lnode *new_element = CreerNode(NULL,item);
	if(element){
		//va a la fin de la liste chain�e
		while(element->link != NULL){
			element = element->link;
		}
		//ajoute la nouvelle node
		element->link = new_element;
	}else{
		//si la iste est vide
    	element=new_element;
	}
}

/* Suppression en "t�te de liste" */
void suppressionTete(Lnode **ph){
	Lnode *to_delete=NULL;
	if(*ph){
		//on garde un pointeur sur l'anciene node pour pouvoir la suprimer
		to_delete = *ph;
		//change la premiere node
		*ph=(*ph)->link;
		//supprime l'anciene node
		free(to_delete);
	}
}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph){
	Lnode *last_node=*ph;
	//si liste non vide
	if(last_node){
		//si liste a plus de 1 element
		if(last_node->link){
			//parcours jusqu'a l'avant dernier element
			while(last_node->link->link){
				last_node = last_node->link;
			}
			free(last_node->link);
			last_node->link = NULL;
		}else{
			//viode entierement la liste
			free(last_node);
			last_node = NULL;
		}
	}
}

/* Proc�dure d'affichage de la liste. Ne doit pas �tre modifi�e!!! */
void listeAffiche(Lnode * ptr){
	if ( NULL == ptr )
		printf("Liste vide!") ;
	else 
		printf("Contenu de la liste : ") ;
	while ( NULL != ptr ) 	{
		printf("%c ",ptr->data);
		ptr = ptr->link ;
		}
	printf("\n") ;
	}

/* Programme principal. Ne doit pas �tre modifi�!!! */
int main(void) {
	Lnode *tete = NULL ;

	listeAffiche(tete) ;
	insertionTete(&tete,'a') ;
	printf("%c ",tete->data);
	listeAffiche(tete) ;
	insertionTete(&tete,'c') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'t') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'s') ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionQueue(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;

   return EXIT_SUCCESS;
   }	
