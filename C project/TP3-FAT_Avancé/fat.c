#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "fat.h"


void initialise_fat(){
	for(int i=0;i<BLOCNUM;i++) FAT[i]=0xFFFF;//on met tous les blocs à 0xFFFF pour les marquer en tant que "bloc libre"
	freeblocks = BLOCNUM;
	obj = NULL;
}


struct objet *rechercher_objet(char *nom){
	struct objet *ptr;//on crée un pointeur
	ptr = obj;//        qui pointe vers le premier objet
	while ( ptr != NULL) {//                     on cycle à travers tous les objets
		if (!strcmp(ptr->nom,nom)) return ptr ;//et si les noms sont identiques, on retourne le pointeur
		ptr = ptr->next;
	}return NULL;// sinon on rertourne NULL
}


int chercher_bloc(int n,int nb_block,int addr_bloc){
	while(addr_bloc<BLOCNUM && FAT[addr_bloc]!=0xFFFF){//tant qu'on ne trouve pas de bloc libre et qu'on à pas atteint la fin du tableau
		addr_bloc++;//									 on incrémente l'addresse
	}
	if (n == nb_block)//si c'est le dernier bloc
		FAT[addr_bloc]=0xFFFE;//on écrit 0xFFFE
	else FAT[addr_bloc]=chercher_bloc(++n,nb_block,addr_bloc+1);//sinon on cherche une addresse pour le bloc suivant
	return addr_bloc;//on renvoit l'addresse du bloc
}
struct objet *creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data){
	int nb_blocks = taille/BLOCSIZE+(taille%BLOCSIZE ? 1:0);//on calcule le nombre de blocs néccéssaires au stockage 
	
	if( rechercher_objet(nom) != NULL){
		printf("%s est déjà présent\n",nom);
		return obj;
	}
	if (nb_blocks>freeblocks ) {
		printf("Pas assez de place pour stocker %s\n",nom);
		return obj;//si il existe un objet du même nom ou qu'il n'y a pas assez de blocs, on quitte
	}
	
	struct objet *nouveau = (struct objet*) malloc(sizeof(struct objet));//on crée un pointeur vers un nouvel objet
	strncpy(nouveau->nom,nom,NAMELEN);//for(long unsigned i=0;i<NAMELEN;i++) nouveau->nom[i] = nom[i]; //i un long unsigned pour la comparaison avec strlen()
	for(int i=strlen(nom); i<NAMELEN; i++)(nouveau->nom)[i]=0; //pad with zeros (est important si la mémoire n'est pas "propre")
	nouveau->auteur = auteur;
	nouveau->taille = taille;
	nouveau-> index = chercher_bloc(0,nb_blocks-1,0);//s'occupe de remplir les blocs du tableau FAT
	nouveau->next = NULL;
	//on remplis la nouvelle structure
	
	struct objet *ptr;
	ptr = obj;
	
	if(ptr!=NULL) {
		while(ptr->next != NULL) {//cherche l'objet en queue de liste
			ptr = ptr->next;
		}
		ptr->next = nouveau; //ajoute le nouvel objet à la queue
	}else obj = nouveau;
	
	int addr_bloc=nouveau->index;
	for(int j=0;j<nb_blocks;j++){//copier les données dans le bloc correspondant
		for(unsigned int i = 0;i<(taille-j*BLOCSIZE) && i<BLOCSIZE;i++){//i en unsigned int pour la comparaison avec taille
			volume[addr_bloc*BLOCSIZE+i]=data[j*BLOCSIZE+i];//copie BLOCSIZE octet dans volume
		}
		addr_bloc=FAT[addr_bloc];
	}
	freeblocks-=nb_blocks;//met à jour le nombre de blocs libre
	return nouveau;//retourne un pointeur vers le nouvel objet (pas demandé dans fat.h ?)
}


void effacer_index(int addr_bloc){//remet tous les bolcs à 0xFFFF récursivement
	if (FAT[addr_bloc]!=0xFFFE) effacer_index(FAT[addr_bloc]);//si ce n'est pas le dernier bloc, on efface le bloc suivant
	FAT[addr_bloc]=0xFFFF;
}
int supprimer_objet(char *nom){
	struct objet *ptr;
	ptr = rechercher_objet(nom);//on passe au pointeur l'addresse de l'objet retourné par la fonction nom
	if (ptr == NULL) return -1;
	
	effacer_index(ptr->index);//pour effacer les blocs marqué par l'objet
	freeblocks+=(ptr->taille)/BLOCSIZE+((ptr->taille)%BLOCSIZE ? 1:0);//met à jour le nombre de blocs libre
	
	if(ptr->next==NULL){//si l'objet est en queue
		if(ptr==obj){//si l'objet est en tête (et donc l'unique objet de la liste)
			supprimer_tout();
		}else{
			free(ptr);//libère la zone mémoire associé au dernier objet
			ptr=obj;
			while ((ptr->next)->next != NULL) {
				ptr = ptr->next;
			}
			ptr->next = NULL;//modifie le pointeur de l'avant dernier objet
		}
	}else{//sinon on copie "l'objet suivant" dans l'objet à supprimer
		for(long unsigned i=0; i<NAMELEN;i++) ptr->nom[i] = (ptr->next)->nom[i];//i en long unsigned pour la comparaison avec strlen()
		ptr->auteur = (ptr->next)->auteur;
		ptr->taille = (ptr->next)->taille;
		ptr->index = (ptr->next)->index;
		struct objet *old_ptr=ptr->next;
		ptr->next = (ptr->next)->next;
		free(old_ptr);//puis on supprime l'ancient "objet suivant"
	}return 0;
}


void supprimer_tout(){
	struct objet *ptr;
	ptr = obj;
	while(ptr!=NULL){
		ptr=obj->next;
		free(obj);//on libère toute la mémoire alloué
		obj=ptr;
	}
	initialise_fat();//puis la fonction initialise fat s'occupe de réinitialiser le reste
}


int lire_objet(struct objet *o,char **data){
	if (o==NULL) return -1;//si l'objet n'existe pas, erreur
	//printf("size of data: %ld\n",sizeof(data));
	//if (sizeof(*data)<o->taille) return -1;//erreur si data ne peut pas contenir toutes les données du fichier (mais sizeof() pas utile ici)
	int addr_bloc = o->index;
	unsigned int size = o->taille;
	int cnt=0;
	while(addr_bloc!=0xFFFE){//copie toutes les données dans data
		for(unsigned int i = 0; i<size-(cnt*BLOCSIZE) && i<BLOCSIZE; i++){//i en unsigned int pour la comparaison avec size
			(*data)[cnt*BLOCSIZE+i] = volume[addr_bloc*BLOCSIZE+i];
		}
		cnt++;
		addr_bloc=FAT[addr_bloc];
	}
	return 0;
}

