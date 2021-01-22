#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <unistd.h> 
#include "AlgoGenetique.h" 
#include <math.h>
#include <time.h>
/*
si i est paire :
	alors c'est une opérande donc + - * /
	comme c'est une opérande on isole les deux bits de poid faible avec un masque
si i est impaire :
	alors on récupère la partie nombre, or elle est localisée sur les 4 bits de poid forts donc on fait un décalage binaire vers la gauche 
*/
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
		affiche(test[i].gene);
		if (expect != test[i].score) printf("error\n"); else printf("success\n"); 
	}
}


void selection(groupe *population,groupe *parents)
{
	//on va récupérer la positions des meilleurs parents sélectionés pour la gen suivante
	int idexes_meilleurs_serpent[NBPARENTS];
	int last_index = 0;
	serpent *membres = population->membres;
	if(NBPARENTS<population->nombre){
		//utiliser la méthode du tri par insertion pour récupérer nos meilleurs indexes
		idexes_meilleurs_serpent[0]=0;
		for(int i = 0 ; i<population->nombre ; i++){
			serpent *candidat = &membres[i];
			//si l'element a i a un meilleur score que le dernier element sauvegarder danbs les plus petits score
			//on va l'nsérer dans la liste des indexe  des meileurs elements
			//en réutilisant l'algorithmùe qui s'apparente au trie par iinsertion
			if(last_index<NBPARENTS || candidat->score < membres[idexes_meilleurs_serpent[last_index]].score){
				//copie de li
				int j=last_index;

				//tant que pas au début de liste, si element i a meilleur score que le score de l'element qui a le plus grand score dans 
				//la liste des NBPARENTS element qui ont le plus petit score
				while(j>=0 && candidat->score < membres[idexes_meilleurs_serpent[j]].score){
					if(j<(NBPARENTS-1)){

						//on décale les indexes vers la droite de 1, si element au bout de la liste on le supprime il ne fait
						//pas partit des 50 meilleurs
						idexes_meilleurs_serpent[j+1]=idexes_meilleurs_serpent[j];
					}
					j--;
				}
				if(j == last_index && last_index<NBPARENTS-1){
					//ajouter un nouvel element dans la liste
					idexes_meilleurs_serpent[j+1]=i;
				}
				else{
					//la liste s'est déplacée et on a fait un trou pour le nouvel element 
					idexes_meilleurs_serpent[j+1]=i;
				}

				if(last_index<NBPARENTS-1){
					last_index++;
				}
			}
		}

		if(last_index!= NBPARENTS-1){
			printf("erreur pas assez de parents pour continuer la generation\n");
			parents = NULL;
		}else{
			int i=0,j = 0;
			
			serpent *acopier; 
			long int moyenne_best = 0;
			//on recopie tous les parents avec les meilleurs score dans l'objet parent
			for(i = 0 ; i<NBPARENTS;i++){
				//le serpent a copier
				acopier = &membres[idexes_meilleurs_serpent[i]];
				//serpent *direct= (parents->membres+i);
				//on utilise des . car membres[i] n'est pas un pointeur mais une case memoire deja reservée pour un serpent
				parents->membres[i].score = acopier->score;
				moyenne_best +=acopier->score/NBPARENTS;
				//copie de l'equation
				for(j = 0;j<NBGENE/2;j++){
					parents->membres[i].gene[j]=acopier->gene[i];
				}
			}
			printf("\tmoyenne best: %ld\n", moyenne_best);

		}
	}else{
		printf("extinction de la population pas assez de parents pour la génération suivante\n");
		parents = NULL;
	}
}

/*
initialise le score des serpent d'un groupe et affiche la moyenne et l'écart type des score pour cette génération
parametre:
	population: le groupe a étudier
*/
int evaluation(groupe *population) 
{
	static int generation = 0;

	int serpent_malefique = 0;
	unsigned long int moyenne = 0;
	unsigned long int ecart_type = 0;
	printf("generation %d:\n",generation);
	if(population){
		for(int i=0;i<population->nombre;i++){
			calcul(&(population->membres[i]));
			serpent_malefique = serpent_malefique || population->membres[i].score==0;
			if(population->membres[i].score==0) affiche(population->membres[i].gene);
			moyenne+=(population->membres[i].score==MAX?0:(population->membres[i].score/population->nombre));
		}
	}else{
		printf("pas de population\n");
	}

	for(int i = 0 ; i<population->nombre ; i++){
		ecart_type += (population->membres[i].score - moyenne)*(population->membres[i].score - moyenne)/population->nombre;
	}
	ecart_type= sqrt(ecart_type);

	printf("\tscore moyen: %lu\n\tecart type: %lu\n",moyenne,ecart_type);
	generation++;

	return !serpent_malefique;
}

/*
Description:
	prend en paramètre une population de serpent et génère un génome aléatoire pour chaque serpent
parametre:
	population: groupe structure avec nombre set qui va initialiser la population aléatoirement
return:
	void
*/
void generationAleatoire(groupe *population)
{

	//compte combien de fois la fonction est appelée, met le compteur a zero si premiere fois 
	srand((unsigned)time( NULL ));
	if(population){
		//on règle la fonction pseudo aléatoire sur une valeur arbitraire pour garder une génération aléatoire exaustive a l'appel de rand
		//si on utilise pas srand le rand() risque de devenir répétitif
		
		int nb_population = population->nombre;
		int index_gene = 0;
		for(int i=0;i<nb_population;i++){
			unsigned char *genotype = population->membres[i].gene;
			
			//creer le genotype tableau de caractères
			for(index_gene=0;index_gene<NBGENE/2;index_gene++){
				genotype[index_gene]=rand()%255; //génère un octet aléatoire
			}
		}
	}else{
		printf("pas de population\n");
	}
}

void reproduction(groupe *population,groupe *parents)
{
	srand((unsigned)time( NULL ));
	serpent *parent1,*parent2,*fils;
	int crossing_over = 0;
	int i=0,i_gen = 0;

	for(i=0;i<population->nombre;i++){

		//on choisis des parents aléatoires parmis les 50 meilleurs

		parent1 = &(parents->membres[rand()%parents->nombre]);
		parent2 = &(parents->membres[rand()%parents->nombre]);

		//parent1 = &(parents->membres[(2*i)%50]);
		//parent2 = &(parents->membres[(2*i+1)%50]);
		crossing_over = rand()%NBGENE;

		//on remplis la population avec des enfants d'élites
		fils = &(population->membres[i]);
		for(i_gen = 0;i_gen<NBGENE/2;i_gen++){
			if(i_gen<crossing_over/2){
				fils->gene[i_gen]=parent1->gene[i_gen];
			}
			else{
				fils->gene[i_gen]=parent2->gene[i_gen];
				if(crossing_over%2!=0 && (i_gen==crossing_over/2)){
					fils->gene[i_gen]=(fils->gene[i_gen]&0x0F) | (parent1->gene[i_gen]&0xF0);
				}
			}
		}
	}
}
void mutation (groupe *population)
{
	srand((unsigned)time( NULL ));
	int mutation = 0, j=0;
	//serpent *a_muter;
	for(int i=0;i<population->nombre;i++){
		for(j=0;j<NBGENE;j++){
			mutation = rand()%30; //1% mutation
			if(mutation==1){
				//mutation = rand()%7;
				population->membres[i].gene[j/2] = j%2?((rand()%(255&0xF0))|(population->membres[i].gene[j/2]&0x0F)):((rand()%(255&0x0F))|(population->membres[i].gene[j/2]&0xF0));
			}
		}
	}
}



