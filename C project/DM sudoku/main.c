#include <stdio.h>     
#include <stdlib.h>
#include "sudoku.h"


#define AUTOMATIQUE 

 
#ifdef AUTOMATIQUE 
int main(int argc,char *argv[]) 
{
	sudoku s; 
	if ((argc != 2) || (!chargerSudoku(s,argv[1]))) { printf("erreur\n"); exit(1); } 
	afficherSudoku(s);

	if ( resoudreSudoku(s) == 1 )  
	afficherSudoku(s);
	return 1; 
}
#else 
int main(int argc,char *argv[]) 
{
	sudoku s;
	uint8_t libres,abandon,c,l,v; 

	initialiserSudoku(s); 
	libres=compterLibres(s); 
    abandon=0;  
    while ((!abandon) && ( libres != 0 )) {
        afficherSudoku(s);
        lireAction(&abandon,&l,&c,&v); 
        
        if ( ! abandon ) {
			if (estValide(s,l,c,v)) {
	            s[l][c]=v; 
                libres=libres-1; 
			}
            else {
				printf("coup impossible\n"); 
		  	}        
        }
	}
    afficherSudoku(s);
	if (abandon) {
        printf("Je suis très déçu !\n"); 
    } else {
        printf("Bravo !\n");	
	}
}

#endif 

