/*
 * AudioDriver.h
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#ifndef AUDIODRIVER_H_
#define AUDIODRIVER_H_

#include <SDL2/SDL.h>

class AudioDriver
{
public:
	static constexpr int CHANNELS = 1;
	static constexpr int SAMPLING_FREQ = 44100;
protected:
	SDL_AudioSpec _spec {};
	SDL_AudioDeviceID _dev {};

public:
	AudioDriver();
	~AudioDriver();

	void queue(const short * data, size_t length);
};



#endif /* AUDIODRIVER_H_ */
