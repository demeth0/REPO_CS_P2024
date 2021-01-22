#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bitmap.h"

/*
Description:
	écrit les 100 premiers nombres impaires dans le fichier impairs.txt, créer si non existant
return:
	void
*/
void writeImpairs(void){
	//ouvre le fichier en mode ecriture
	FILE *file_pointer = NULL;
	file_pointer = fopen("nombres_impairs.txt", "w");

	//si on peut ouvrir le fichier
	if(file_pointer != NULL){
		for(int i=0;i<100;i++){
			//écrir les 100 premiers nombres impairs
			fprintf(file_pointer, "%d ", 1+i*2);
		}
	}
	//fermer le fichier
	fclose(file_pointer);
}

/*
Description:
	compte le nombre de voyelles majuscule ou minuscules dans file 
parameter:
	file: le fichier text dont on vas compter les voyelles
return:
	le nombre de voyelles majuscules ou minuscules dans le fichier file
*/
int voyelles(char* file){
	//ouvre le fichier en mode lecture
	FILE *file_pointer = NULL;
	file_pointer = fopen(file, "r");
	//compteur de voyelles
	int nb_voy = 0;
	if(file_pointer){
		char letter = 0;

		//tant que l'on lis des données
		while(fread(&letter, sizeof(char), 1, file_pointer)){
			//on passe tout les caracteres majuscules en minuscules
			letter = letter < 96 ? letter+32 : letter;
			
			//si c'est une voyelle
			if(letter == 97 || letter == 101 || letter == 105 || letter == 111 || letter == 117 || letter == 121){
				nb_voy++;
			}
		}
	}
	//fermer le fichier
	fclose(file_pointer);
	return nb_voy;
}

/*
Description:
	décripte le message cacher dans le texte.
return:
	void
*/
void decryptText(void){
	FILE *textFile = NULL;
	FILE *source=NULL;
	textFile = fopen("ressource/transporteur.txt","r");
	source=fopen("source.txt","w");
	if(textFile && source){
		unsigned char octet = 0,decoded_octet=0;
		int counter=0;
		//pour chaque caractère dans le fichier transporteur
		while(fread(&octet, 1,1,textFile)){
			//is une lettre
			if(isalpha(octet)){
				//si en majuscule ecire 1
				if(isupper(octet)){
					//convention little-endian
					decoded_octet += 1<<(7-counter);
				}
				counter++;

				//quand on a lue 8 caracteres alors on enregistre l'octet
				if(counter==8){
					counter=0;
					fwrite(&decoded_octet,1,1,source);
					//on vide l'octet
					decoded_octet=0;
				}
			}
		}

		fclose(textFile);
		fclose(source);
	}
}

/*
Description:
	si le decalage est a 8 alors l'octet est calculer a partir d'un tableau de 8 bits et est ecrit dans le fichier
parameter:
	byte: le tableau de 8 bits (char 0 ou 1)
	decalage: la conditiona vérifier pour faire le calcul qui sera aussi reset a 0 si validée
	output_flux: fichier sortie d'écriture de l'octet
return:
	void
*/
void checkByte(unsigned char* byte,int *decalage, FILE* output_flux){
	//si le tableau de bits est remplis
	if((*decalage)==8){
		//remise a 0
		(*decalage)=0;
		//octet a calculer
		unsigned char byte_val=0;
		for(int i = 0 ;i<8;i++){
			//on décale le bit en fonction de sa position dans le tableau en little-endian
			byte_val += byte[i]<<(7-i);
			//remise a zero du tableau pour eviter des erreurs
			byte[i]=0;
		}
		//ecriture du resultat
		fwrite(&byte_val,sizeof(char),1,output_flux);
	}
}

/*
Description:
	décripte un message en concatenant les bit de poid faible de chaque couleur de chaque pixel du fichier transporteur de format bmp
return:
	void 
*/
void decryptImage(void){
	//prépare les fichiers in et out pour utilisation
	FILE *file_pointer_output = NULL,*file_pointer_transporter = NULL;
	file_pointer_output = fopen("source.bmp", "w");
	file_pointer_transporter = fopen("ressource/transporteur.bmp", "r");

	if(!(file_pointer_output && file_pointer_transporter)){
		return;
	}

	fichierEntete fileHeader={};
	//lis l'entete du fichier
	fread(&fileHeader, 14, 1, file_pointer_transporter);

	//affiche l'entete du fichier
	printf("signature: %d\n", fileHeader.signature);
	printf("tailleFichier: %d\n", fileHeader.tailleFichier);
	printf("reserve: %d\n", fileHeader.reserve);
	printf("offset: %d\n", fileHeader.offset);

	//lis l'entete des données de l'image
	imageEntete imageHeader = {};
	fread(&imageHeader,40,1,file_pointer_transporter);

	//affiche l'entete de l'image
	printf("\ntailleEntete: %d\n", imageHeader.tailleEntete);
	printf("largeur: %d\n", imageHeader.largeur);
	printf("hauteur: %d\n", imageHeader.hauteur);
	printf("plan: %d\n", imageHeader.plan);
	printf("profondeur: %d\n", imageHeader.profondeur);
	printf("compression: %d\n", imageHeader.compression);
	printf("tailleImage: %d\n", imageHeader.tailleImage);
	printf("resolutionHorizontale: %d\n", imageHeader.resolutionHorizontale);
	printf("resolutionVerticale: %d\n", imageHeader.resolutionVerticale);
	printf("nombreCouleurs: %d\n", imageHeader.nombreCouleurs);
	printf("nombreCouleursImportantes: %d\n", imageHeader.nombreCouleursImportantes);

	//buffer qui va stocker les couleurs bvr
	couleurPallete pixel;
	//compteur pour concatener les bit de poid faible par groupe de 8
	int decalage = 0;
	//la liste des 8 derniers bits de poid faible lus
	unsigned char buffer[8];
	//mask pour extraire le bit de poid faible des valeurs des couleurs
	unsigned char mask = 1;
	//indexe d'itération
	int i = 0 ;
	
	for(i = 0 ; i < (imageHeader.hauteur*imageHeader.largeur) ; i++){

		//lis données BVR du pixel
		fread(&pixel, 3,1, file_pointer_transporter);

		//récupération du bit de poid faible de la couleur et incrémente le compteur du buffer
		buffer[decalage] = pixel.B & mask;
		decalage++;
		checkByte(buffer,&decalage,file_pointer_output);

		buffer[decalage] = pixel.V & mask;
		decalage++;
		checkByte(buffer,&decalage,file_pointer_output);

		buffer[decalage] = pixel.R & mask;
		decalage++;
		checkByte(buffer,&decalage,file_pointer_output);
	}

	//le dernier octet a ecrire dans le fichier sortie, remplir de zero le reste du tableau
	char lastByte = 0;
	for(int i = 0 ; i<decalage;i++){
		lastByte+=buffer[i]<<(7-i);
	}
	fwrite(&lastByte,1,1,file_pointer_output);

	//fermeture des fichiers
	fclose(file_pointer_output);
	fclose(file_pointer_transporter);
}

/*
Description:
	lis un bit a la position donnée dans l'octet fournis et retourne la valeur de l'octet
*/
char getBit(char octet,int pos){
	//on décale vers la droite pour positionner le bit a la position n a la position 0
	//on applique un masque pour ne garder que le bit a la position 0
	return (octet>>(7-pos))&1;
} 

/*
Description:
	lis l'octet si sa pos est a 8 (fini d'ajouter les bits) on lis l'octet suivant de file
parameter:
	byte: l'octet lus
	pos: le 'pointeur de lecture', 8 si on a lus tout les bits
	file: le fichier d'ou lire l'octet suivant
*/
void nextOctet(char *byte, int *pos,FILE *file){
	if((*pos)==8){
		//remise a 0 du compteur
		(*pos)=0;
		//lecture de l'octet
		if(!fread(byte,1,1,file)){
			//si fin de fichier metre un octet de 0
			(*byte)=0;
		}
	}
}

/*
Description:
	ecrit un fichier source dans les bits de poid faible des palettes de couleurs des pixel de l'image originel
return:
	void
*/
void encryptImage(void){
	FILE *original=NULL;
	FILE *source = NULL;
	FILE *transporter=NULL;
	
	original = fopen("ressource/originel_1.bmp","r");
	source = fopen("ressource/source.bmp","r");
	transporter = fopen("transporteur.bmp","w");
	//si on n'a pas reussi a ouvrir les fichiers
	if(!(original && source && transporter)){
		return;
	}

	//lecture de l'entet du fichier original
	fichierEntete fileHeader={};
        fread(&fileHeader, 14, 1, original);
        imageEntete imageHeader = {};
        fread(&imageHeader,40,1,original);

	//copie de l'entet dans le fichier transporter
	fwrite(&fileHeader, 14,1,transporter);
	fwrite(&imageHeader,40,1,transporter);

	//buffer qui va stocker les couleurs bvr
        couleurPallete pixel;
	//le mask pour supprimer le bit de poid faible des couleurs du pixel
	char pixel_mask = '\xfe';
	//la byte a metre dans les bits de poid faible
	char source_byte = 0;
	//initialisation du byte
	fread(&source_byte,1,1,source);
	//nb de bits mis dans l'image transporter sur les 8 bit du byte n de l'image source
	int decalage=0;
	for(int i=0;i<(imageHeader.hauteur*imageHeader.largeur) ; i++){
		//recupere le pixel
		fread(&pixel,3,1,original);
		
		//change le bit de poid faible avec un des bits du fichier source
		pixel.B = (pixel.B&pixel_mask)+getBit(source_byte,decalage);
		//passe au bit suivant a ecrire
		decalage++;
		//passe a l'octet suivant si besoin
		nextOctet(&source_byte,&decalage,source);

		pixel.V = (pixel.V&pixel_mask)+getBit(source_byte,decalage);
                decalage++;
		nextOctet(&source_byte,&decalage,source);
		
		pixel.R = (pixel.R&pixel_mask)+getBit(source_byte,decalage);
                decalage++;
		nextOctet(&source_byte,&decalage,source);
		
		//ecriture du pixel modifier
		fwrite(&pixel,3,1,transporter);
	}
	
	//on remplis la fin du fichier transporter avec les données du fichier original
	char buffer=0;
	while(fread(&buffer, 1,1,original)){
		fwrite(&buffer,1,1,transporter);
	}

	fclose(source);
	fclose(transporter);
	fclose(original);
}

int main(){
	//writeImpairs();
	//decryptText();
	//encryptImage();
	//decryptImage();
	return 0;
}


