#include "fonctions.h"
//voila

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return (x&y)^((~x)&z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return (x&y)^(x&z)^(y&z);
}

uint32_t SHR(uint32_t x, unsigned short int n){
	return x>>n;
}

uint32_t ROTR(uint32_t x, unsigned short int n){
	return (x>>n) | (x<<(32-n));
}

uint32_t Epsilon0(uint32_t x){
	return ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22);
}

uint32_t Epsilon1(uint32_t x){
	return ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25);
}

uint32_t Sigma0(uint32_t x){
	return ROTR(x,7) ^ ROTR(x,18) ^ SHR(x,3);
}

uint32_t Sigma1(uint32_t x){
	return ROTR(x,17) ^ ROTR(x,19) ^ SHR(x,10);
}