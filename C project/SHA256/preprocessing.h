#ifndef SHA256_PREPROCESSING

#define SHA256_PREPROCESSING

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 64 //taille en octet
#define BLOCK_SIZE_BIT 512 //taille en bit



typedef struct DataLinkedList{
	unsigned char content[BLOCK_SIZE];
	struct DataLinkedList * next; 
	struct DataLinkedList * back; 
}DataLinkedList, *DLL;

/*
	union use one memory adresse for multiple variable types
	struct mean for saving a uint64 as a char array
*/
union size_s {
	uint64_t i;
	unsigned char c[sizeof(uint64_t)];
};

DLL data, queue;
unsigned int DLLSize;
int addBlock(unsigned char *new_data);
void deleteBlock();
void deleteAllBlock();
void afficher();
void initialiseList();
int preprocessing();

#endif