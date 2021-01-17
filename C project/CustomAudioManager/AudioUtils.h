#ifndef CUSTOM_AUDIO_UTILS
#define  CUSTOM_AUDIO_UTILS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>
#include <MMSystem.h>


typedef struct {
	uint32_t size;					//taille en octet de l'audio
	unsigned short channels;		//le nombre de channelmono si 1
	uint32_t sample_rate;			//la fréquence d'écriture de l'audio (nombre d'enregistrement par seconde)
	unsigned short block_align;		//le nombre de channel multiplier par le nombre d'octet par enregistrement
	unsigned short bit_per_sample;	//le nombre de bit pour un enregistrement
	uint32_t byte_rate;				//le nombre d'octet en une seconde
}CustomAudioData, *LPCustomAudioData;			//LP is a windows convention for struct pointer

void CreateAudioData(LPCustomAudioData audioData, uint32_t size, unsigned short channels, uint32_t sample_rate, unsigned short bit_per_sample);
void PlayAudio(LPCustomAudioData audioData, char* data);

#endif