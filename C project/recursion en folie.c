#include <stdlib.h> 
#include <stdio.h>

int addition_rec(int a,int b){
	if (b==0){
    	return a;
	}
	else{
    	return addition_rec(a+1,b-1);
	}
}

int soustraction_rec(int a,int b){
	if (b==0){
    	return a;
	}
	else{
    	return addition_rec(a-1,b-1);
	}
}

int produit_rec(int a,int b){
	if(a==0 || b==0){
		return 0;
	}
	if(a>b)
		return addition_rec(produit_rec(a,b-1),a);
	else
		return addition_rec(produit_rec(b,a-1),b);
}

int puissance_rec(int a,int n){
	if(n==0){
		return 1;
	}else{
		return produit_rec(a,puissance_rec(a,n-1));
	}
}

int factoriel_rec(int a){
	if(a<=0){
		return 1;
	}
	return produit_rec(a,factoriel_rec(a-1));
}

int fibonachi(int n){
	if(n==0)
		return 0;
	else if(n==1)
		return 1;

	return addition_rec(fibonachi(n-1),fibonachi(n-2));
}

int main(int argc, char const *argv[])
{
	int t = fibonachi(10);
	printf("%d\n", t);
	return 0;
}