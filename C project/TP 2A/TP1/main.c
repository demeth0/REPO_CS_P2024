#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

/*
Description:
	inverse deux entier, a=b et b=a apres le programme.
parametre:
	a: preier entier
	b: deuxieme entier
return:
	void
*/
void swap(int* a, int* b){
	int c=*a;
	*a=*b;
	*b=c;
}

/*
Description:
	trie une liste d'entier par ordre croissant.
parametre:
	tab: un tableau d'entier
	size: la taille du tableau
return:
	void
*/
int BubbleSort(int* tab, int size){
	//l'indexe qui parcours le tableau
	int indexe = 0;
	int operations=0;
	//valeur booleenne qui verifie si l'algorithme a effectuer une inversion
	unsigned short permuted = 1;
	while(permuted){
		permuted=0;
		for(indexe=0;indexe<size-1;indexe++){
			//si la valeur d'aprés est plus grand que la valeur en indexe
			operations++;
			if(tab[indexe+1]<tab[indexe]){
				//inversion des valeurs
				swap(&tab[indexe],&tab[indexe+1]);
				//si on fait une inversion on continue
				permuted=1;
			}
		}
	}
	return operations;
}

/*
Description:
        trie les entiers dans le tableau d'entier en parametre dans l'ordre croissant
parametre:
        tab: un tabelau d'entiers
        size: taille du tableau
return:
        void
*/
int insertionSort(int *tab, int size){
	int j,v, operations=0;
	for(int i=0;i<size;i++){
		//copie de l'indexe i
		j=i;
		//copie de la valeur a l'indexe i
		v=tab[i];
		//on décale tout les nombres plus grand que tab[i] de 1 vers la droite
		while(j>0 && v<tab[j-1]){
			tab[j]=tab[j-1];
			j--;
			operations++;
		}
		//on pose tab[i] a l'emplacement qu'ona libérer en déplacant les valeurs vers la droite
		tab[j]=v;
		//on peut executer la boucle while car toute les valeurs avant i sont triée
	}
	return operations;
}
/*
Description:
	fusionne deux tables triée en une table triée
parameter:
	tab: les deux tabs triées collée l'une a la suite de l'autre
	temp: table vide de meme taille quetab
	left: début indexe premiere table
	mid: début table deux et fin table une
	right: fin table deux
	cnt: pointeur vers le compteur d'opération
return:
	void
*/
void merge(int *tab, int *tmp, int left, int mid, int right, int* cnt){
	//les indices des tableau
	int indtab1=0,indtab2=0, indtmp=0;
	//tant que il reste des elements dans le preier et deuxieme tableau
	while(indtab1<mid-left || indtab2<right-mid){
		(*cnt)++;
		//si on a pas fini de parcourir les deux tableau
		if(indtab1<mid-left && indtab2<right-mid){
			//le quel des deux tableau a le plus grand indice
			if(tab[left+indtab1]<tab[mid+indtab2]){
				tmp[indtmp]=tab[left+indtab1];
				indtmp++;
				indtab1++;
			}else{
				tmp[indtmp]=tab[mid+indtab2];
				indtmp++;
				indtab2++;
                        }
		//ici si on a fini de parcourir un des deux tableau alors on rajoute le reste du deuxieme a la fin
		}else{
			if(indtab1<mid-left){
				tmp[indtmp]=tab[left+indtab1];
				indtmp++;
				indtab1++;
			}else{
				tmp[indtmp]=tab[mid+indtab2];
				indtmp++;
				indtab2++;
			}
		}
	}

	for(int i = 0 ; i<right-left;i++){
		(*cnt)++;
		tab[left+i]=tmp[i];
	}
}

/*
Description:
	partie récursive du trie fusion
parameter:
	tab: le tableau d'entier
	left: index du debut du tableau
	right: index de la fin du tableau
return:
	le nombre d'opération
*/
int mergeSortRec(int *tab, int left,int right){
	int cnt=0;
	//si le tableau a plus de un elements
	if((right-left)>1){
		//milieu du tableau
		int mid=(right-left)/2;
		
		//trie premiere partie du tableau
		cnt += mergeSortRec(tab,left, left+mid);
		//trie deuxieme partie du tableau
		cnt+= mergeSortRec(tab,left+mid, right);
		//creer tableau vide temporaire
		int *tmp=malloc((right-left)*sizeof(int));
		//fusionne les deux tableau trier en un tableau trirer de talle right-left
		merge(tab,tmp, left, left+mid, right, &cnt);
		free(tmp);
	}
	
	return cnt;
}

/*
Description:
	fonction de trie fusion
parameter:
	tab: le tableau d'entier a trier
	size: la taille du tableau
*/
int mergeSort(int *tab, int size){
	int cnt=0;
	cnt += mergeSortRec(tab, 0, size);
	return cnt;
}

int main(){
	int ref[]  = {3,6,6,7,8,10,14,15,17,19,20,21,23,25,26,28,28,28,32,32,34,35,38,38,39,43,44,46,48,49,50,58,59,62,64,65,69,71,75,79,79,79,81,84,86,89,92,93,97,99};
	int tab1[] = {14,15,92,65,35,89,79,32,38,46,26,43,38,32,79,50,28,84,19,71,69,39,93,75,10,58,20,97,49,44,59,23,07,81,64,06,28,62,8,99,86,28,03,48,25,34,21,17,06,79};
	int tab2[] = {99,97,93,92,89,86,84,81,79,79,79,75,71,69,65,64,62,59,58,50,49,48,46,44,43,39,38,38,35,34,32,32,28,28,28,26,25,23,21,20,19,17,15,14,10,8,7,6,6,3};
	int tab3[] = {3,6,6,7,8,10,14,15,17,19,81,21,23,25,26,28,28,28,32,32,34,35,38,38,39,43,44,46,48,49,50,58,59,62,64,65,69,71,75,79,79,79,20,84,86,89,92,93,97,99};
	
	int n = sizeof(ref)/sizeof(int);

	affiche(tab1, n);

	return 0;
}


