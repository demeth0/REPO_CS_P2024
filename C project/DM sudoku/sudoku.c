#include <stdio.h>     
#include <stdlib.h>
#include <string.h>
#include "sudoku.h" 

void afficherSudoku(sudoku s) 
{
	uint8_t i,j; 
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
	
	for (i=0;i<9;i++) {
		for (j=0;j<9;j++) {
			printf("%d ",s[i][j]); 
		}
		printf("\n"); 
	}
}

// cette fonction retourne 1 s'il est valide de poser la valeur n sur  la case (x, y) en vérifiant la règle Horizontale (Chaque ligne doit contenir les 9 chiffres de 1 à 9 – On teste donc s'il existe une case sur la ligne x contenant déjà la valeur n).
// retourne  0 sinon. 
uint8_t estValideH(sudoku s,uint8_t x,uint8_t y,uint8_t n)
{
	uint8_t i = 0;
	uint8_t isValid = estVide(s,x,y,n);
	while(isValid && i<9){
		isValid = (s[i][y]!=n);
		i++;
	}
	return isValid;
}
// cette fonction retourne 1 s'il est valide de poser la valeur n sur la case (x, y) en vérifiant la règle Verticale  (Chaque colonne doit contenir les 9 chiffres de 1 à 9 – On teste donc s'il existe une case sur la colonne y contenant déjà la valeur n), 
// retourne 0 sinon. 
uint8_t estValideV(sudoku s,uint8_t x,uint8_t y,uint8_t n)
{
	uint8_t i = 0;
	uint8_t isValid = estVide(s,x,y,n);
	while(isValid && i<9){
		isValid = s[x][i]!=n;
		i++;
	}
	return isValid;
}


// cette fonction retourne 1 s'il est valide de poser la valeur n sur la case (x, y) en vérifiant la règle Region  (Chaque région doit contenir les 9 chiffres de 1 à 9 – On teste donc s'il existe une case dans la région contenant déjà la valeur n). 
// retourne 0 sinon. 
uint8_t estValideR(sudoku s,uint8_t x,uint8_t y,uint8_t n)
{
	uint8_t i = 0;
	uint8_t isValid = estVide(s,x,y,n);
	uint8_t posX,posY;
	while(isValid==1 && i<9){
		posX = x-x%3+i%3; //x-x%3 => premiere case de la région ; i%3 => position ligne 
		posY = y-y%3+i/3; //y-y%3 => premiere case de la région ; i/3 => position colonne 
		isValid = (s[posX][posY]!=n?1:0);
		i++;
	}
	return isValid;
}

// cette fonction retourne 1 s'il est valide de poser la valeur n sur la case (x, y) en vérifiant les règles du sudoku 
// retourne 0 sinon. 
uint8_t estValide(sudoku s,uint8_t x,uint8_t y,uint8_t n)
{
	return estVide(s,x,y,n) && estValideR(s,x,y,n) && estValideV(s,x,y,n) && estValideH(s,x,y,n);
}


// cette fonction retourne 1 si la case (x,y) est vide.  
// retourne 0 sinon. 
uint8_t estVide(sudoku s,uint8_t x,uint8_t y,uint8_t n)
{	
	return s[x][y]==0;
}

// cette fonction compte le nombre de case (x,y) vide.  
// retourne ce nombre  
uint8_t compterLibres(sudoku s)
{
	int x=0,y=0;
	uint8_t libres=0;
	for(x=0;x<9;x++){
		for(y=0;y<9;y++){
			if(s[x][y]==0){
				libres ++;
			}
		}
	}

	return libres;
}

// cette fonction retourne 1 s'il n'y a plus de case vide dans la grille. 
// retourne 0 sinon. 
// prend en paramètre une grille de sudoku, parcourt toute cette grille ligne après ligne afin de trouver dans la grille la première case vide pour laquelle il y a le moins de possibilités en respectant les règles précédentes. 
// positionne les coordonnées de cette case dans x et y, ainsi que le nombre min de possibilités dans nb. 
uint8_t trouveMin(sudoku s,uint8_t *x,uint8_t *y,uint8_t *n) 
{
	uint8_t no_case_vide=1;
	if(compterLibres(s)!=0){
		no_case_vide=0;
		uint8_t pos_x=0,pos_y=0, trouver_meilleur=0;
		
		uint8_t nb_possibilite=0, n_i=0;
		*n=10;
		uint8_t num_case = 0;
		
		while(num_case<81 &&!trouver_meilleur){
			//calcul des coordonées
			pos_x=num_case%9;
			pos_y=num_case/9;

			if(estVide(s,pos_x,pos_y,0)){
				//si la case est vide alors on va chercher le nombre de chiffre différents qu'on peut luis assigner
				nb_possibilite=0;

				//on test pour 1 a 9
				for(n_i=1;n_i<10;n_i++){
					//si on peut mettre le chiffre
					if(estValide(s,pos_x,pos_y,n_i)){
						//on peut luis mettre un chiffre de plus en possibilitée
						nb_possibilite++;
					}
				}

				//si meilleur possibilitée que le précédent (moin)
				if(nb_possibilite<*n){
					//met a jour les fields
					*n=nb_possibilite;
					*x=pos_x;
					*y=pos_y;
					//si i ln'a qu'une possiblitée alors forcément le meilleur
					if(nb_possibilite==1){
						//on arrete 
						trouver_meilleur=1;
					}
				}
			}

			num_case++;
		}
	}
	return no_case_vide;
}


// cette fonction qui s'appelle récursivement permet de résoudre une grille de sudoku. 
// retourne 1 si la grille est terminée 
// retourne 0 si on ne trouve pas de solution. 
uint8_t resoudreSudoku(sudoku s) 
{
    uint8_t x,y,n;
    uint8_t nombre;
    uint8_t resolue = 0;

    //trouve une position potentiel
    resolue=trouveMin(s,&x,&y,&n);

    //le nombre min a tester
    nombre = 1;

    //tant que non résolue
    while(resolue==0 && nombre <= 9){
        //si on peut poser le nombre alors
        if(estValide(s,x,y,nombre)){
            //on met le nombre
            s[x][y] = nombre;

            //on essaye de résoudre le sudoku avec la nouvelle hypothèse
            resolue = resoudreSudoku(s);
            //si échoue
            if(resolue==0){
                //on enleve le nombre car impossible de résoudre avec cette hypothèse
                s[x][y] = 0;
            }
        }
        //nombre suivant
        nombre++;
    }

    //retourne si résolue ou non
    return resolue;
}

void initialiserSudoku(sudoku s) 
{
	sudoku save={{6,1,0,8,0,0,0,0,5}, 
		  {0,2,5,0,0,0,0,3,8}, 
		  {0,0,8,0,5,0,1,0,4}, 
		  {0,8,0,0,4,1,3,0,9}, 
		  {0,6,0,5,8,7,0,1,0}, 
		  {1,0,4,9,2,0,0,8,0}, 
		  {8,0,6,0,1,0,2,0,0}, 
		  {2,4,0,0,0,0,5,6,0}, 
		  {5,0,0,0,0,2,0,4,7}}; 

	memcpy(s,save,sizeof(sudoku)); 
}

void sauveSudoku(char *path,sudoku s) 
{
}

void lireAction(uint8_t *abandon,uint8_t *l,uint8_t *c,uint8_t *v)
{	
	printf("abandon ?Y/N\n");
	unsigned char ab=0; 
	scanf("%1s",&ab);
	if(ab =='Y'){
		*abandon=1;
	}else{
		unsigned int a,b,k;
		printf("ligne :\n");
		scanf("%u",&a);
		printf("colonne :\n");
		scanf("%u",&b);
		printf("nombre :\n");
		scanf("%u",&k);

		uint8_t a1,b1,c1;
		a1=a;
		b1=b;
		c1=k;

		*l=a1;
		*c=b1;
		*v=c1;
	}
}

uint8_t chargerSudoku(sudoku s, char *path) 
{
	FILE *fo; 
	int ret=1; 
	printf("Opening %s\n",path); 
	if ((fo=fopen(path,"r"))==NULL) return 0; 
	if (fread(s,sizeof(sudoku),1,fo) != 1) { 
		ret=0;
	}
	fclose(fo);
	return ret;  
}
