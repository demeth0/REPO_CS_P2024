#ifndef CUSTOM_WAV_DECODER
#define CUSTOM_WAV_DECODER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct WAVriffChunk{
    unsigned char identifier[4];
    uint32_t size;
    unsigned char format[4];
}WAVRiffChunk,*LPWAVRiffChunk;

typedef struct WAVChunkPCM{
    unsigned char identifier[4];
    uint32_t size;
    unsigned short audio_format;
    unsigned short nb_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    unsigned short block_align;
    unsigned short bit_per_sample;
}WAVChunkPCM,*LPWAVChunkPCM;

typedef struct WAVdataChunk{
    unsigned char identifier[4];
    uint32_t size;
}WAVDataChunk,*LPWavDataChunk;

char * readPCMWavFile(FILE *wav_file, LPWAVRiffChunk riffC, LPWAVChunkPCM wavC, LPWavDataChunk dataC);

#endif