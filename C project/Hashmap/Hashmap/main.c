#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    int key;
    int value;
} Node;

typedef struct Hashmap{
    int size;
    Node **list_node;
} Hashmap;

Hashmap *createHashmap(int size){
    Hashmap *map = (Hashmap*)malloc(sizeof(Hashmap));
    map->size = size;
    map->list_node = (Node**)malloc(sizeof(Node*)*size);
    for(int i=0;i<size;i++)
        map->list_node[i] = NULL;
    return map;
}
int hashCode(Hashmap *map,int key){
    if(key<0)
        return -(key%map->size);
    return key%map->size;
}



int main()
{
    printf("starting\n");
    Hashmap *map = createHashmap(10);
    char simple_str[] = "test";
    printf(simple_str);
    return 0;
}
