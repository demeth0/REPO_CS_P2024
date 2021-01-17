#ifndef FONCTIONS_SHA256
#define FONCTIONS_SHA256
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
	opération de décalage binaire vers la droite
	0 <= n < 32
*/
uint32_t SHR(uint32_t x, unsigned short int n);

/*
	opération de rotation binaire
*/
uint32_t ROTR(uint32_t x, unsigned short int n);

/*
	formules magiques
*/
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

uint32_t Epsilon0(uint32_t x);

uint32_t Epsilon1(uint32_t x);

uint32_t Sigma0(uint32_t x);

uint32_t Sigma1(uint32_t x);

#endif