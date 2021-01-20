/*
 * AudioDriver.cc
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#include "AudioDriver.h"
#include <stdexcept>
#include <string>

AudioDriver::AudioDriver()
{
	using namespace std::literals;

	_spec.channels = CHANNELS;
	_spec.freq = SAMPLING_FREQ;
	_spec.format = AUDIO_S16;
	_spec.samples = 512;

	_dev = SDL_OpenAudioDevice(nullptr, 0, &_spec, &_spec, 0);
	if (_dev < 2)
		throw std::runtime_error(
				"Не удалось открыть звуковое устройство: "s +
				SDL_GetError());

	SDL_PauseAudioDevice(_dev, 0);
}

AudioDriver::~AudioDriver()
{
	SDL_PauseAudioDevice(_dev, 1);
	SDL_CloseAudioDevice(_dev);
}

void AudioDriver::queue(const short * data, size_t length)
{
	SDL_QueueAudio(_dev, data, length * sizeof(short));
}



