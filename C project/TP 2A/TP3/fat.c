#include <stdlib.h>
#include <stdio.h>
#include "fat.h"
#include <string.h>

/*int compare256String(char* str1,char* str2){
	int ans = 1;
	int index = 0;
	//tanta que lettres identiques et pas fini de parcourir le texte
	while(ans==1 && index<256){
		//identiques ?
		ans = (*(str1+index))==(*(str2+index));
		//lettre suivante
		index++;
	}
	return ans;
}*/

void initialise_fat(){
	freeblocks = BLOCNUM; // le bloc fff8 est réservé
	for(int i=0;i<BLOCNUM;i++){
		FAT[i]=0xffff;
	}
	obj=NULL;
}

struct objet *rechercher_objet(char *nom){
	int found_obj = 0;
	struct objet *copy = obj;
	
	//tant que il reste des elements dans la liste chainée
	while(copy != NULL && !(found_obj==1)){
		//si on retrouve l'element
		if(strcmp(copy->nom,nom)==0){
			//arrete la boucle
			found_obj = 1;
		}else{
			//sinon element suivant
			copy = copy->next;
		}
	}
	// si on a pas trouver l'element retourner NULL
	// car a la fin de la liste l'element est NULL 

	return copy;
}

struct objet *creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data){

	//calcul le nombre de block a enregistrer
    unsigned short nb_blocs = (taille/BLOCSIZE)+(taille%BLOCSIZE==0?0:1);
    unsigned short block_saved = 0;
    int last_espace_libre = 0;
    int compteur=0;
    int i=0;

    struct objet *new_element = NULL;
    //si fichier pas dans volume et encore place dans volume
    if(freeblocks > nb_blocs && rechercher_objet(nom)==NULL){
		//creer element
		new_element=malloc(sizeof(struct objet));
		//reserver l'espace
		freeblocks -= nb_blocs;
		//initialise l'objet
		if(strlen(nom)<NAMELEN){
    		strcpy(new_element->nom,nom);
		}

		new_element->auteur=auteur;
		new_element->taille=taille;

		//pour chaque espace memoire de FAT 
		while(block_saved<nb_blocs){
			//si espace libre et nb_blocs>0
	    	if (FAT[compteur]== 0xFFFF/* && block_saved<nb_blocs*/){

	    		//enregistrement des données dans le volume a la bonne  position
	    		for(i=0;i<BLOCSIZE;i++){
	    			//BLOCSIZE*block_saved = position 0 dans les donnée (début du block)
	    			if((i+BLOCSIZE*block_saved)<taille)
	    				volume[compteur*BLOCSIZE+i]= data[i+BLOCSIZE*block_saved];
	    			else
	    				volume[compteur*BLOCSIZE+i]=0;
	    		}

	    		//si c'est le premier block
	    		if(block_saved==0){
	    			new_element->index=compteur;
	    		}else{
	    			//si ce n'est pas le premier block enregistrer alors on met dans fat[ancien block pos]=next pos (compteur)
	    			FAT[last_espace_libre]=compteur;
	    		}
				//enregistrement de l'indexe
				last_espace_libre=compteur;
				//un bloc de moin a enregistrer
				block_saved++;
				//si on a tout enregistrer alors ce block dans FAT est le dernier
				compteur++;
			}

		}

		FAT[last_espace_libre]=0xfffe;
		new_element->next = obj;
		obj = new_element;
	}
	return new_element;
}

int supprimer_objet(char *nom){
	struct objet *element = rechercher_objet(nom);

	int supprime = -1;
	if(element!=NULL){
		if(element==obj){
			obj=obj->next;
		}
		//on sauvegarde le bout de la liste chainée apres l"element a supprimer
		struct objet *next_element=element->next;

		//on libere les cases memoir
		unsigned short indexe = element->index, temp=0;
		while(FAT[indexe] != 0xFFFE){
			temp = FAT[indexe];
			FAT[indexe]=0xFFFF;
			indexe =temp;
			freeblocks++;
		}
		FAT[indexe]=0xFFFF;
		freeblocks++;
		element->next =NULL;
		

		struct objet *tete = obj;
		
		//cas particulier element==obj/element est premier element de la liste
		if(strcmp(obj->nom, element->nom)==0){
			tete=obj;
			//met a jour la tete de liste
			obj=obj->next;
			//supprime le premier element
			free(tete);
			supprime = 0;
		}else{
			//on se déplace jusqu'a l'avant dernier element avant le null si on peut, ici l'element juste avant l'element a supprimer car element->next =NULL;
			while(tete->next !=NULL && tete->next->next != NULL){
				tete = tete->next;
			}

			//on racroche le reste de la liste chainee
			tete->next = next_element; //tete->next pointait vers element

			//on libere l'element a supprimer
			free(element);
			supprime = 0;
		}

	}
	return supprime;
}

void supprimer_tout(){
	//buffer qui va liberer les ressources
	struct objet *element_a_liberer;
	while(obj!=NULL){
		element_a_liberer=obj;
		//on parcours la liste
		obj = obj->next;
		//on supprime l'element précédent
		free(element_a_liberer);
	}
	//on remet FAT et freebloc a 0
	initialise_fat();
}

/*
Description:
	va récupérer les informations dans le volume correspondant a l'objet o et les metres dans data
*/
int lire_objet(struct objet *o,char **data){
	int succes = -1;
	if(o!=NULL){
		succes = 0;
		//premier index de block de donnée dans le volume
		int fat_index= o->index;
		//le nombre de bloc enregistrés dans data
		int bloc_saved = 0;
		//on assigne les données dans un pointeur temporaire
		char *donnee = malloc(o->taille);
		int i=0;

		while(FAT[fat_index] != 0xfffe){
			for(i=0;i<BLOCSIZE;i++){
				//pour chaque donnée dans le volume on les rajoute a la fin de donnee
				donnee[bloc_saved*BLOCSIZE+i]=volume[fat_index*BLOCSIZE+i];
			}
			//bloc de donnée suivant dans volume
			fat_index = FAT[fat_index];
			//on décale l'index 0 dans donnee
			bloc_saved++;
		}
		for(i=0;i<(o->taille%BLOCSIZE);i++){
			//pour chaque donnée dans le volume on les rajoute a la fin de donnee
			donnee[bloc_saved*BLOCSIZE+i]=volume[fat_index*BLOCSIZE+i];
		}

		//on lie les deux pointeur 
		*data = donnee;
	}

	return succes;
}


int main(void){
	initialise_fat();
	int i=0;

    char nom[]= "salut";
    unsigned short auteur  = 13;
    
    char data[]="salut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un testsalut c'est un test";
	unsigned int taille = sizeof(data);


    creer_objet(nom,auteur, taille, data);
    char *r_data = NULL;
    lire_objet(obj,&r_data);

    for(i=0;i<obj->taille;i++){
    	printf("%c", r_data[i]);
    }
	return 0;
}
