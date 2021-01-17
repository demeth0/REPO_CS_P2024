/*
Description:
    program to manage audio, record play edit process ... with windows library

Author:
    Samuel Dechambre
    
sources:
    https://stackoverflow.com/questions/36708989/audio-recording-and-real-time-playing-in-windows-using-wavein-and-waveout
    https://docs.microsoft.com/en-us/windows/win32/multimedia/recording-waveform-audio
    https://stackoverflow.com/questions/11725528/save-wave-file-using-waveinopen
    https://docs.microsoft.com/en-us/previous-versions/ms713499(v=vs.85)
    https://pubs.opengroup.org/onlinepubs/009696799/basedefs/stdint.h.html
    https://sites.google.com/site/musicgapi/technical-documents/wav-file-format
    https://developer.blackberry.com/native/documentation/graphics_multimedia/audio_video/tutorial_play_a_wav_structure_of_a_wav_file.html
    http://odl.sysworks.biz/disk$axpdocsep002/progtool/mmserv22/mmeos007.htm
    https://stackoverflow.com/questions/2351659/how-to-get-pcm-data-from-microphone-in-c-os-windows
    https://gist.github.com/Jon-Schneider/8b7c53d27a7a13346a643dac9c19d34f

    https://www.geeksforgeeks.org/function-pointer-in-c/
    https://www.newty.de/fpt/fpt.html
    https://stackoverflow.com/questions/9986972/callback-function-in-waveoutopen-api
    https://docs.rs/winapi/0.3.7/winapi/um/mmsystem/type.HWAVEOUT.html
    https://docs.microsoft.com/en-us/windows/win32/multimedia/playing-waveform-audio-files
    https://www.tutorialspoint.com/cprogramming/c_strings.htm
    https://stackoverflow.com/questions/34591193/confusion-with-malloc-through-function-argument
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>
#include <MMSystem.h>
#include "AudioUtils.h"
#include "CustomWavDecoder.h"

int main(int argc, char const *argv[])
{

	CustomAudioData audioData;
	char* data_buffer;

    FILE *data_file = fopen("docci-docci.wav","rb");
	WAVRiffChunk riff_c;
    WAVChunkPCM wav_c;
    WAVDataChunk data_c;

    data_buffer = readPCMWavFile(data_file, (LPWAVRiffChunk) &riff_c, (LPWAVChunkPCM) &wav_c, (LPWavDataChunk) &data_c);

    audioData.size = data_c.size;
    audioData.channels = wav_c.nb_channels;
    audioData.sample_rate = wav_c.sample_rate;
    audioData.block_align = wav_c.block_align;
    audioData.bit_per_sample = wav_c.bit_per_sample;
    audioData.byte_rate = wav_c.byte_rate;
    
	PlayAudio((LPCustomAudioData)&audioData, data_buffer);

    free(data_buffer);
    fclose(data_file);
	return 0;
}