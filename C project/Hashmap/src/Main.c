#include <stdio.h>
#include <stdlib.h>
//include du fichier .h pour le pre-processoring
#include "Main.h"

//une node représente un couple clée valeur
typedef struct Node {
	int key;
	int value;
	struct Node *next;
} Node;

//l'objet hashmap c'est l'objet qui contien tout nos couples cles valeur
typedef struct {
	int size;
	//sous liste de couples pour eviter des grosses recherches dans une meme liste
	Node **node_list;
} Hashmap;

//reserve the memory space for the hashmap 
Hashmap *createHashmap(int size){
	//resserve global space for the hashmap
	Hashmap *map = (Hashmap*)malloc(sizeof(Hashmap));
	//initialize size
	map->size = size;
	//reservate space for the sub list of the hashmap
	map->node_list = (Node**)malloc(sizeof(Node*)*size);
	int i;
	for(i = 0 ; i< size; i++){
		//initialize pointer of the sub list
		map->node_list[i] = NULL;
	}
	return map;
}

//arythmetic operation for node repartition in the sub table of the hashmap
int hashCode(Hashmap *map, int key, int value){
	int hash = 0;
	if(key < 0){
		hash = -(key%map->size);
	}else{
		hash = key%map->size;
	}
	return hash;
}

void insert(Hashmap *map, int key, int value){

}

//fonction main
int main(){
	printf("start");
	Hashmap *test = createHashmap(5);
	return 0;
}