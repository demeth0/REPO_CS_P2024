#include "CustomWavDecoder.h"

char * readPCMWavFile(FILE *wav_file, LPWAVRiffChunk riffC, LPWAVChunkPCM wavC, LPWavDataChunk dataC){
	fread(riffC, sizeof(WAVRiffChunk),1,wav_file);
	fread(wavC, sizeof(WAVChunkPCM),1,wav_file);
	fread(dataC, sizeof(WAVDataChunk),1,wav_file);
	char *p_data = malloc(dataC->size+1);
	if(p_data==NULL){
		printf("memory allocation failed\n");
	}else{
		fread(p_data, dataC->size,1,wav_file);
		p_data[dataC->size]='\0';
	}

	return p_data;
}