#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <unistd.h> 
#include "AlgoGenetique.h" 


#define lire(gene,i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4); 

void affiche(unsigned char *gene)
{
	char code[]="+-*/"; 
	int i=0,res;  
	// the last gene is useless 
	while (i<(NBGENE-1)) {
		res=lire(gene,i); 
		if (i%2)
			printf("%c ",code[res%4]); 
		else 
			printf("0x%x ",res);	
		i=i+1; 
	}
	printf("\n"); 
}

/*
calcul et initialise le score d'un serpent
parametre:
	g: le serpent
*/
void calcul(serpent *g)
{
	if(g){
		int score = 0;
		int buffer = 0;
		int next_buffer = 0;
		unsigned char *gene = g->gene;

		//ici on va utiliser un identifieur,
		//si identifieur = -1 alors le buffer n'est pas initialiser
		//si identifieur = 0 alors on doit ajouter buffer a score
		//si identifieur = 1 alors on doit soustraire le buffer au score
		//si identifieur = 2 alors il faut faire un produit 
		//si identifieur = 3 alors il faut faire une division 
		unsigned char identifieur = 0;

		//-1 car on ne lis pas les 4 derniers bits
		for(int i = 0;i<NBGENE-1;i++){
			//si opérande (i%2==1)
			if(i%2){
				identifieur=lire(gene,i);
				identifieur=identifieur %4;

			//si nombre
			}else{
				//on lis le nombre dans le gene
				next_buffer = lire(gene,i);
				switch(identifieur){
					//case somme 
					case 0:
						//on peut ajouter le buffer au score ils sont séparer avec un +
						//dans l'expression on aurais score+buffer+next_buffer(+*/-)...
						score+=buffer;
						buffer=next_buffer;
						break;
					//case soustraction 
					case 1:
						//on peut ajouter le buffer au score ils sont séparer avec un -
						score+=buffer;
						buffer=-1*next_buffer; //attention on a une soustraction par contre donc on ajoute -next buffer dans 
						//l'expression on aurais score+buffer-next_buffer(+*/-)...
						break;
					//case multiplication
					case 2:
						//on a un produit donc on multiplie buffer et next buffer
						//score + buffer * next_buffer(+*/-)...
						buffer=buffer*next_buffer;
						break;
					//case division
					case 3:
						//on a une division
						//score + buffer / next_buffer(+*/-)...
						if(next_buffer!= 0)
							buffer=buffer/next_buffer;
						else{
							g->score= MAX; //divison par 0 on arrete le programme car le calcul n'est pas possible 
							return;
						}

						break;
				}
			}
		}
		//additioner dernier nombre
		score += buffer;
		//fin du calcul
		g->score= abs(score-SEEK);
	}else{
		printf("pas de serpent\n");
	}
	
}


void testCalcul() 
{
int i,expect; 
serpent test[]={
	{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660},
	{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87",735},
	{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c",694},
	{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3",646},
	{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63",MAX},
	{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\xf2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5",543},
	{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302},
	{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9",MAX},
	{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd",MAX},
	{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3",MAX},
	{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa",727}
	}; 

	for(i=0;i<sizeof(test)/sizeof(serpent);i++) {
		expect=test[i].score; 
		calcul(&test[i]);
		if (expect != test[i].score) 
			printf("error\n");  
		else
			printf("succes\n");
	}
}


int main(void)
{
	testCalcul();
	return 0;
}