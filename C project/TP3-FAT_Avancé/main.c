#define _GNU_SOURCE 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "fat.h"


/* Programme en plus pour afficher les objets */
void listeAffiche(){
	struct objet *ptr;
	ptr = obj;
	if ( NULL == ptr )
		printf("\nListe vide!") ;
	else 
		printf("\nContenu de la liste : \n") ;
	while ( NULL != ptr ) 	{
		printf("nom: %s \n",ptr->nom);
		printf("auteur: %d \n",ptr->auteur);
		printf("taille: %d \n",ptr->taille);
		printf("index: %d \n",ptr->index);
		ptr = ptr->next ;
		}
	printf("\n") ;
	}
	
unsigned int get_file_size(FILE *fp){ //return file size in bytes
    fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);
	rewind(fp);
	return size;
}

int file_dont_exist(char * filename){
	if (access( filename, F_OK )!=0){//vérification présence fichier
		printf("File %s was not found\n",filename);
		return 1;
	}
	return 0;
}

int size_dont_match(char * filename,unsigned int size,unsigned int target_size){//gestion d'erreur taille
	printf("size %s= %d\n",filename,size);
	if(size<target_size){
		printf("Attention: fichier %s anormalement petit\nTaille requise: %d\n",filename,target_size);
		return 1;
	}else if(size>target_size){
		printf("Erreur: fichier %s trop grand\nTaille requise: %d\n",filename,target_size);
		return -1;
	}
	return 0;
	}

void set_text_color(unsigned int a){
	switch(a%7){
	case 0: printf("\033[0;39m");
	break;
	case 1: printf("\033[0;31m");
	break;
	case 2: printf("\033[0;32m");
	break;
	case 3: printf("\033[0;33m");
	break;
	case 4: printf("\033[0;34m");
	break;
	case 5: printf("\033[0;35m");
	break;
	case 6: printf("\033[0;36m");
	break;
	case 7: printf("\033[0;37m");
	break;
	}
}

/* Programme principal. */
int main(int argc, char *argv[]) {
	initialise_fat();
	//get arg, si none create new, else read inputs
	int opt;
	unsigned int size;
	FILE * part_file=NULL;
	unsigned short author=0;
	
	while ((opt = getopt(argc, argv, "XP:hs:r:d:a:l")) != -1) {
		switch (opt) {
		case 'P':
			printf("Using specified partition %s\n",optarg);
			if (file_dont_exist(optarg)){ 
				printf("Creating %s\n",optarg);
				part_file = fopen(optarg,"w");
			}else{
				part_file = fopen(optarg,"r+");
				fread(FAT, sizeof(unsigned short)*BLOCNUM, 1, part_file);
				fread(volume, sizeof(char)*BLOCSIZE*BLOCNUM, 1, part_file);
				if (0xAD!=getc(part_file)) {printf("The FAT partition %s may be corrupted, aborting\n",optarg);
				exit(EXIT_FAILURE);}
				char name[NAMELEN];
				while(fread(name, sizeof(char)*NAMELEN, 1, part_file)){
					struct objet *nouveau = (struct objet*) malloc(sizeof(struct objet));
					strncpy(nouveau->nom, name, NAMELEN);
					fread(&(nouveau->taille), sizeof(unsigned int), 1, part_file);
					fread(&nouveau->auteur, sizeof(unsigned short), 1, part_file);
					fread(&nouveau->index, sizeof(unsigned short), 1, part_file);
					struct objet *ptr;
					ptr = obj;
					if(ptr!=NULL) {
						while(ptr->next != NULL)ptr = ptr->next;
						ptr->next = nouveau;
					}else obj = nouveau;
			}}
			break;
		case 'a':
			if ((author =atoi(optarg))==0)
				printf("The specified author ID is not a number.\n");
		}
		
	}
	if (!part_file) printf("No partition file specified, using the default one: %s\n", DEFAULT_PARTITION);
	if (!part_file && access( DEFAULT_PARTITION, F_OK )==0){//if a default partition is present, initialise 
		part_file = fopen(DEFAULT_PARTITION,"r+");
		fread(FAT, sizeof(unsigned short)*BLOCNUM, 1, part_file);
		fread(volume, sizeof(char)*BLOCSIZE*BLOCNUM, 1, part_file);
		if (0xAD==getc(part_file)) {
			char name[NAMELEN];
			while(fread(name, sizeof(char)*NAMELEN, 1, part_file)){
				struct objet *nouveau = (struct objet*) malloc(sizeof(struct objet));
				strncpy(nouveau->nom, name, NAMELEN);
				fread(&(nouveau->taille), sizeof(unsigned int), 1, part_file);
				fread(&nouveau->auteur, sizeof(unsigned short), 1, part_file);
				fread(&nouveau->index, sizeof(unsigned short), 1, part_file);
				struct objet *ptr;
				ptr = obj;
				if(ptr!=NULL) {
					while(ptr->next != NULL)ptr = ptr->next;
					ptr->next = nouveau;
				}else obj = nouveau;
			}
			part_file = fopen(DEFAULT_PARTITION,"w");
		}else {
			initialise_fat();
			fclose(part_file);
			part_file=NULL;
		}
	}
		
	optind=1;//allow multiple instance of getopt
	while ((opt = getopt(argc, argv, "XP:hs:r:d:a:l")) != -1) {
                switch (opt) {
				case 'h':
					printf("Full documention:\n");
					printf("Options:\n");
					printf("	-h :display help (this)\n");
					printf("	-P [path/to/file]:specify the FAT_partition file\n");
					printf("	-s [path/to/file]:specify the file to be stored in the emulated FAT partition\n");
					printf("	->	-a [author]:specify the file to be stored's author ID (unsigned short)\n");
					printf("	-r [name of file]:specify the name of the file to retrieve\n");
					printf("	-d [name of file]:specidy the name of the file to be deleted in the emulated FAT partition\n");
					printf("	-l :display the FAT partition's content\n");
					printf("	-X :print and format the content of the FAT table and volume\n");
					printf("Note:\n");
					printf("	If -P is not used, the DEFAULT_PARTITION (%s) will be used if present\n", DEFAULT_PARTITION);
					exit(EXIT_SUCCESS);
					break;
				case 's':
					if (file_dont_exist(optarg)) exit(EXIT_FAILURE);
					
					{//parenthesis limit the scope of data[] which is an array of variable size, a workaround would be using malloc
					FILE * file_to_store = fopen(optarg,"r");
						//get taille
					size = get_file_size(file_to_store);// see line 28
						//store data in array
					char data[size];
					fread(data, size, 1, file_to_store);
						//get auteur
					if(!author){
					printf("Using default author ID: 26985\n");
					author = 26985;//HEX:6969
					}
						//créer_objet
					creer_objet(optarg,author,size,data);
					for (int i=0;i<10;i++) printf("%c",data[i]);
					fclose(file_to_store);
					}
					break;
				case 'r':
					{
					struct objet *file_to_retrieve;//crée un pointeur vers une structure objet
					file_to_retrieve = rechercher_objet(optarg);//le pointeur pointe vers l'objet qu'on veut lire
					if (file_to_retrieve != NULL) {//si l'objet existe
						char container[file_to_retrieve->taille];//on crée un tableau à la bonne taille
						char *p = container;// on crée un pointeur vers ce tableau
						lire_objet(file_to_retrieve,&p);//on passe l'adresse de ce tableau a la fonction pour qu'elle y copie les données
						FILE * file_out = fopen(file_to_retrieve->nom,"w");
						for(unsigned int i=0; i<file_to_retrieve->taille;i++){//i en unsigned int pour la comparaison avec taille
							putc(container[i],file_out);//on copie les donnée récupéré dans un fichier pour voir si on obtient le fichier d'origine
						}
						fclose(file_out);
					} else printf("Object doesn't exist\n");
					}
					break;
				case 'd':
					if (supprimer_objet(optarg)==-1) printf("Object doesn't exist\n");
					else printf("object succesfully deleted\n");
					break;
				case 'l':
					printf("\nCurrent content of the FAT partition:");
					listeAffiche();
					break;
                case 'P': part_file = fopen(optarg,"w");
                    break;
                case 'a':
                    break;
				case 'X': ;
					unsigned int cnt=0;
					unsigned int color=1;
					printf("\nFAT table at address 0x000000 - 0x%06lX\n",sizeof(FAT)-1);
					for (int i=0;i<BLOCNUM/5+(sizeof(FAT)%5 ? 1:0);i++){
						printf("0x%06X",i*10);
						for(int j=i*5;j<(i*5+5) && j<BLOCNUM; j++){
							set_text_color(++color);
							printf(" %02X %02X",FAT[j]&0xFF,FAT[j]>>8&0xFF);
						}printf("\033[0m\n");
					}
					printf("\nvolume at address 0x%06lX - 0x%06lX\n",sizeof(FAT),sizeof(FAT)+sizeof(volume)-1);
					for (int i=0;i<sizeof(volume)/10+(sizeof(volume)%10 ? 1:0);i++){
						printf("0x%06lX",i*10+sizeof(FAT));
						set_text_color(color);
						for(int j=i*10;j<(i*10+10) && j<BLOCSIZE*BLOCNUM; j++){
							if (cnt++%BLOCSIZE==0) set_text_color(++color);
							printf(" %02X",volume[j]);
						}printf("	\033[0m");
						for(int j=i*10;j<(i*10+10) && j<BLOCSIZE*BLOCNUM; j++){
							printf(" %c",volume[j]);
						}printf("\n");
					}
					break;
                default: /* '?' */
                    fprintf(stderr, "Usage: %s [-P] [-s [-a] ] [-r] [-d] [-l] [-X] \n Use -h to print help\n",argv[0]);
                    exit(EXIT_FAILURE);
                }
        }
	
	/**Place each memory zone in their own file*/
	if (part_file==NULL) part_file = fopen(DEFAULT_PARTITION,"w"); else ftruncate(part_file,get_file_size(part_file));
	fwrite(&FAT, sizeof(FAT), 1, part_file);//met le contenu de FAT dans 
	fwrite(volume, sizeof(volume), 1, part_file);
	putc(0xAD,part_file);//sort of checksum
	struct objet *ptr = obj;
	while (ptr!=NULL){
		fwrite(ptr->nom, NAMELEN, 1, part_file);
		fwrite(&ptr->taille, sizeof(unsigned int), 1, part_file);
		fwrite(&ptr->auteur, sizeof(unsigned short), 1, part_file);
		fwrite(&ptr->index, sizeof(unsigned short), 1, part_file);
		ptr=ptr->next;
	}
	
	supprimer_tout();
	fclose(part_file);
	
	return EXIT_SUCCESS;
   }	