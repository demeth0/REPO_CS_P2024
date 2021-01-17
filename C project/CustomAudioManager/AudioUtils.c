#include "AudioUtils.h"



/*
	remplis une structure AudioData
*/
void CreateAudioData(LPCustomAudioData audioData, uint32_t size, unsigned short channels, uint32_t sample_rate, unsigned short bit_per_sample){
	audioData->size=size;
	audioData->channels = channels;	
	audioData->sample_rate = sample_rate;
	audioData->bit_per_sample=bit_per_sample;

	audioData->block_align = channels*(bit_per_sample/8);
	audioData->byte_rate = audioData->block_align*sample_rate; 
}

LPWAVEFORMATEX generateFormatTex(LPCustomAudioData audioData, WORD format, WORD cbSize){
	//create WAVEFORMATEX
	LPWAVEFORMATEX audio_format = malloc(sizeof(WAVEFORMATEX));
	if(audio_format!=NULL){
		audio_format->wFormatTag = format;
		audio_format->nChannels = audioData->channels;
		audio_format->nSamplesPerSec=audioData->sample_rate;
		audio_format->wBitsPerSample = audioData->bit_per_sample;
		audio_format->nBlockAlign = audioData->block_align;
		audio_format->nAvgBytesPerSec = audioData->byte_rate;
		audio_format->cbSize = cbSize;
	}

	return audio_format;
}


/*
	event handler function 
*/
void CALLBACK AudioPlayerEventHandler(HWAVEOUT hwo,UINT uMsg,DWORD_PTR dwInstance,DWORD_PTR dwParam1,DWORD_PTR dwParam2){
	switch(uMsg){
		case MM_WOM_CLOSE:
		//printf("close\n");
		break;
		case MM_WOM_DONE:
		//printf("done\n");
		break;
		case MM_WOM_OPEN:
		//printf("open\n");
		break;
	}
}

/*
	play a PCM format audio, data char array must be terminated with a NULL
*/
void PlayAudio(LPCustomAudioData audioData, char* data){
	//reserve memory for buffer
	HWAVEOUT audioOutputHandler;

	/*
    MMSYSERR_NOERROR if successful
    MMSYSERR_BADERRNUM Specified error number is out of range.
    MMSYSERR_NODRIVER No device driver is present.
    MMSYSERR_NOMEM Unable to allocate or lock memory. 
    */
    MMRESULT command_result = 0;

	//create WAVEFORMATEX
	LPWAVEFORMATEX audio_format ;
	audio_format = generateFormatTex(audioData, WAVE_FORMAT_PCM, 0);
	if(audio_format==NULL){
		printf("system error when creating format tex \n");
		return; //exit point / crash system
	}
	/*
	openning driver for diffusion

	MMRESULT waveOutOpen(
	   LPHWAVEOUT     phwo,					//poitner HWAVEOUT buffer for audio handler
	   UINT_PTR       uDeviceID,			//WAVE_MAPPER auto select device 
	   LPWAVEFORMATEX pwfx,					//audio format data
	   DWORD_PTR      dwCallback,			//function that handle events
	   DWORD_PTR      dwCallbackInstance,	//data to send to the callback function
	   DWORD          fdwOpen				//type of callback function here event handler
	);
	*/
	command_result = waveOutOpen((LPHWAVEOUT)&audioOutputHandler, WAVE_MAPPER, audio_format, (DWORD_PTR)AudioPlayerEventHandler, 0L, CALLBACK_FUNCTION);
	if(!(command_result==MMSYSERR_NOERROR)){
		printf("system error when opening wave driver for writting\n");
		return; //exit point / crash system
	}

	//preprocessing for audio diffusion
	/*
	typedef struct wavehdr_tag {
	  LPSTR              lpData;
	  DWORD              dwBufferLength;
	  DWORD              dwBytesRecorded;
	  DWORD_PTR          dwUser;
	  DWORD              dwFlags;
	  DWORD              dwLoops;
	  struct wavehdr_tag  *lpNext;
	  DWORD_PTR          reserved;
	} WAVEHDR, *LPWAVEHDR;
	*/
	WAVEHDR AudioDataBuffer;

	AudioDataBuffer.lpData = (LPSTR)data;
	AudioDataBuffer.dwBufferLength = audioData->size;
	AudioDataBuffer.dwFlags = 0L | WHDR_BEGINLOOP | WHDR_ENDLOOP; //begining and end of the loop
	AudioDataBuffer.dwUser = 0L;
	AudioDataBuffer.dwLoops = 1L;

	/*
	waveOutPrepareHeader(
   		HWAVEOUT  hwo,
   		LPWAVEHDR pwh,
    	UINT      cbwh
	);   
	*/

	command_result = waveOutPrepareHeader(audioOutputHandler,&AudioDataBuffer,sizeof(AudioDataBuffer));
	if(!(command_result==MMSYSERR_NOERROR)){
		printf("system error when preparing header\n");
		waveOutClose(audioOutputHandler);
		return; //exit point / crash system
	}

	/*
	MMRESULT waveOutWrite(
	  HWAVEOUT  hwo,
	  LPWAVEHDR pwh,
	  UINT      cbwh
	);
	*/

	command_result = waveOutWrite(audioOutputHandler,&AudioDataBuffer,sizeof(AudioDataBuffer));
	if(!(command_result==MMSYSERR_NOERROR)){
		printf("system error when playing the audio\n");
		waveOutClose(audioOutputHandler);
		return; //exit point / crash system
	}
	do{
		//wait for the buffer to be filled
		/*
		waveOutUnprepareHeader(
		  HWAVEOUT  hwo,
		  LPWAVEHDR pwh,
		  UINT      cbwh
		);
		*/
		command_result = waveOutUnprepareHeader(audioOutputHandler,&AudioDataBuffer,sizeof(AudioDataBuffer));
		//printf("still playing\n");
	}while(command_result==WAVERR_STILLPLAYING);

	free(audio_format);
	waveOutClose(audioOutputHandler);
}