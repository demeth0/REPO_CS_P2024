

#include "preprocessing.h"

/*
Implémentation File :
	ajoute un élément en queue
*/
int addBlock(unsigned char *new_data){
	DLL block = malloc(sizeof(DataLinkedList));

	if(block){
		block->next = NULL;
		for(int i = 0 ;i<BLOCK_SIZE;i++){
			block->content[i] = new_data[i];
		}

		//si la liste est déja remplie
		if(data){
			block->back = queue;   //on pointe vers l'ancien dernier élément
			queue->next = block;   //on lie l'élément a la liste
			queue = block;         //le nouvel élément est la nouvelle queue
		}else{
			block->back = NULL;    //pas d'éléments avant celui la
			queue = block;         //on initialise la liste a block
			data = block;          //la queue et le la tete son les memes
		}
		DLLSize ++;
		return 0;
	}else{
		fprintf(stderr, "l'allocation dynamique a échouée\n");
		//on fait pas d'exit failure car ca risque de laisser des données résiduelles dans le système
		//il faudra supprimer la liste de donnée avant de quitter le programme 
		return -1;
	}
}


/*
Implémentation File :
	supprime un élément en tête
*/
void deleteBlock(){
	if(data){						//si laliste n'est as vide
		DLL a_supprimer = data; 		//l'ancienne tête
		data = data->next; 			//la nouvelle tête
		free(a_supprimer); 			//libère la mémoire de l'ancienne élément
		if(data){					//si la nouvelle tête n'est pas nulle ca veu dire pile non vide
			data->back = NULL;		//on ne peut pas remonter la liste preière élément
		}else{
			queue=NULL;
		}
		DLLSize --;
	}
}

/*
	suppression de la liste
*/
void deleteAllBlock(){
	DLL old_element = NULL;
	while(data != NULL){
		old_element = data;
		data =data->next;
		free(old_element);
	}
	queue=NULL;
	DLLSize = 0;
}


/*
	lecture et affichage des block a partir de la tete
*/
void afficher(){
	//%x

	DLL tete = data;
	int i=0;
	while(tete){
		//afficher block
		printf("data block %d: \n", i++);
		for(int i =0;i<BLOCK_SIZE;i++){
			printf(" 0x%02x", tete->content[i]);
		}
		printf("\n");
		tete = tete->next;
	}
}

/*
	création de la liste
*/
void initialiseList(){
	data=NULL;
	queue=NULL;
	DLLSize = 0;
}

int preprocessing()
{
	FILE *data_file = fopen("message.txt", "rb");

	//if we can open the file
	if(data_file){
		/*
			LECTURE DES DONNEES
		*/
		
		unsigned char buffer[BLOCK_SIZE];
		int data_read = -1;
		union size_s size; //uint car la taille est positive
		size.i = 0;
		while((data_read = fread(buffer, 1,BLOCK_SIZE,data_file))==BLOCK_SIZE){
			addBlock(buffer);										//ajout le block de donnée dans la file
			if(size.i > (size.i+BLOCK_SIZE)){
				fprintf(stderr, "data overflow, too much data to process\n");
				deleteAllBlock();
				return 0;
			}
			size.i += BLOCK_SIZE*8; //ajoute le block pour chaque lecture de 64
		}
		if(size.i > (size.i+data_read)){
			fprintf(stderr, "data overflow, too much data to process\n");
			deleteAllBlock();
			return 0;
		}
		size.i += data_read*8;   //ajoute le dernier block incomplet ? ou 0 si paritée de 64 des données
		/*
			PREPROCESSING
		*/

		//on fait un calcul sur le dernier block pour savoir si il y a la place de mettre un int 64bit, 

		//le dernier block data est forcément suivit par un 1 puis pas k zero de tell sorte que longueur+1+k%56=0
		//le résultat est le nombre d'octet de 0 a rajouter car on fait du traitement sur des octets
		unsigned short int new_block = (data_read+1)%(BLOCK_SIZE-8); //si =0 alors on a pile la place
		if(new_block == 0){
			buffer[data_read] = 1<<7; // 1000 0000
			data_read++;

			//on enregistre directement la taille a la suite dans le block
			// la taille est sous la forme suivante : abcdefgh on enregistre les octet uns par uns 

			//on enregistre les 8 octet du nombre taille
			for(int i=0;i<8;i++){
				buffer[data_read+i]=size.c[7-i]; //on enregistre les octets en little endian 
			}

		}else{
			if(data_read<(BLOCK_SIZE-8)){ //on remplis de 0 jusqu'a 56 puis on enregistre la taille
				buffer[data_read] = 1<<7; // 1000 0000
				data_read++;

				for(;data_read<(BLOCK_SIZE-8);data_read++){
					buffer[data_read]=0;
				}
			}else{
				
				int i=0;   //position de l'indexe dans le dernier buffer de donnée

				//cas particulier dernier bit a 1 quand buffer plein
				if(data_read==BLOCK_SIZE){
					addBlock(buffer);   // enregistre le block déjà plein
					buffer[i] = 1<<7; 	// 1000 0000 on rajoute le bit a 1
					i++;  				// on décale l'idexe
				}else{
					buffer[data_read] = 1<<7;          // ajout du bit a 1 a la suite du block (encore assez de place)
					data_read++;
					for(int i =0;data_read+i<BLOCK_SIZE;i++){  // on complete le block
						buffer[data_read+i]=0;
					}
					//enregistre le block
					addBlock(buffer);
				}

				//on remplis de 0 jusqu'a laisser juste assez pour la taille
				for(;i<(BLOCK_SIZE-8);i++){
					buffer[i] = 0;
				}
				data_read = i+1; // on a enregistrer i+1 donnée dans le buffer (donnée en 0)
			}

			//on enregistre les 8 octet du nombre taille
			for(int i=0;i<8;i++){
				buffer[data_read+i]=size.c[7-i]; //on enregistre les octets en little endian 
			}

			//ajouter le dernier block a la liste
			addBlock(buffer);

		}

		/*
			DÉBUT DE L'ALGORITHME DE HACHAGE SHA256 (pas fait)
		*/

		afficher();
		fclose(data_file);
	}

	return 1;
}