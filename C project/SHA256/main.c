/*
algo SHA256

sources:
	https://qvault.io/2020/07/08/how-sha-2-works-step-by-step-sha-256/
	https://fr.wikipedia.org/wiki/SHA-2
	https://en.wikipedia.org/wiki/SHA-2

Samuel Dechambre
*/

#include "preprocessing.h"
#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_32UINT 0xFFFFFFFF

union CharInt32 {
	uint32_t i;
	unsigned char c[4];
};

int main(int argc, char const *argv[])
{
	initialiseList();
	int state = preprocessing();
	if(state){
		// gros tas de constantes
		uint32_t K_256[] = {0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
				 0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
				 0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
				 0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
				 0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
				 0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
				 0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
				 0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
		uint32_t H[] = {0x6a09e667,
					  0xbb67ae85,
					  0x3c6ef372 ,
					  0xa54ff53a ,
					  0x510e527f ,
					  0x9b05688c ,
					  0x1f83d9ab ,
					  0x5be0cd19 };


		//début SHA256
		//see https://fr.wikipedia.org/wiki/SHA-2#Calcul_du_condens%C3%A9_(hach%C3%A9)
		DLL tete = data; //copie de la tete
		// idexes, i=nb de block codés, w_i=indexe de W , t= indexe de l'algo principale
		unsigned int w_i=0, t=0;

		// mots 32b pour hachage (16 premiers = block 512b+46 valeurs dérivées)
		uint32_t W[64];

		//variable pour l'algo de hachage
		uint32_t a,b,c,d,e,f,g,h,T1,T2;
		//variable utilisée pour convertir 4 octet en un int32
		union CharInt32 temp;
		while(tete){
			//remplissage des 16 premiers mot 32b pas de modifications
			for(w_i=0;w_i<16;w_i++){
				//on veut récupérer 32 bit soit 4 octet
				//déplacement 4 par 4
				temp.c[0]=tete->content[w_i*4+3];  //remplissage inversé car pas la meme endianitée
				temp.c[1]=tete->content[w_i*4+2];
				temp.c[2]=tete->content[w_i*4+1];
				temp.c[3]=tete->content[w_i*4];
				//convertion en int32
				W[w_i]=temp.i;
				
			}


			for(;w_i<64;w_i++){
				//remplissage des valeurs dérivés
				W[w_i]=(Sigma1(W[w_i-2])+W[w_i-7]+Sigma0(W[w_i-15])+W[w_i-16])%MAX_32UINT;
			}


			a=H[0];    //initialisation des variables
			b=H[1];
			c=H[2];
			d=H[3];
			e=H[4];
			f=H[5];
			g=H[6];
			h=H[7];

			for(t=0;t<64;t++){
				//les supers calcul du SHA256
				T1=(h+Epsilon1(e)+Ch(e,f,g)+K_256[t]+W[t])%MAX_32UINT;
				T2=(Epsilon0(a)+Maj(a,b,c))%MAX_32UINT;
				h=g;
				g=f;
				f=e;
				e=(d+T1)%MAX_32UINT;
				d=c;
				c=b;
				b=a;
				a=(T1+T2)%MAX_32UINT;
			}


			H[0]=(a+H[0])%MAX_32UINT;           //mise a jours des éléments de la clés
			H[1]=(b+H[1])%MAX_32UINT;
			H[2]=(c+H[2])%MAX_32UINT;
			H[3]=(d+H[3])%MAX_32UINT;
			H[4]=(e+H[4])%MAX_32UINT;
			H[5]=(f+H[5])%MAX_32UINT;
			H[6]=(g+H[6])%MAX_32UINT;
			H[7]=(h+H[7])%MAX_32UINT;

			//next element
			tete=tete->next;
		}
		//printf("%d\n", DLLSize);
		printf("%08x%08x%08x%08x%08x%08x%08x%08x\n", H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7]);  //compression de la clés
	}


	deleteAllBlock();  //libération de la mémoire
	return state;
}

//e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855