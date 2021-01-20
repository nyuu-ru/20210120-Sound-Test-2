/*
 * Window.cc
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#include "Window.h"
#include <string>
#include <stdexcept>


static const double freq_table[] {
		130.813, 138.591, 146.832, 155.563, // 4 октава
		164.814, 174.614, 184.997, 195.998,
		207.652, 220.000, 233.082, 246.942,
		261.626, 277.183, 293.665, 311.127, // 5 октава
		329.628, 349.228, 369.994, 391.995,
		415.305, 440.000, 466.164, 493.883,
		523.251, 554.365, 587.330, 622.254, // 6 октава
		659.255, 698.456, 739.989, 783.991,
};

Window::Window()
{
	using namespace std::literals;

	_window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
					"Sound Window",
					SDL_WINDOWPOS_CENTERED_DISPLAY(1),
					SDL_WINDOWPOS_CENTERED_DISPLAY(1),
					1920, 1080,
					SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (_window == nullptr)
		throw std::runtime_error(
				"Не могу создать окно: "s +
				SDL_GetError());

	_renderer = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(_window.get(), -1,
					SDL_RENDERER_ACCELERATED),
			SDL_DestroyRenderer);
	if (_renderer == nullptr)
		throw std::runtime_error(
				"Не могу создать рендерер: "s +
				SDL_GetError());

	_next_event = clk::now() + std::chrono::milliseconds(100);
}

void Window::main_loop()
{
	SDL_Event event;
	const Uint8 * keys = SDL_GetKeyboardState(nullptr);

	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
			handle_event(event);
		}
		handle_keys(keys);

		logic();

		render();
		SDL_RenderPresent(_renderer.get());
	}
}

void Window::handle_event(const SDL_Event & event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		_volume = 3500.;
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_Z: _gen.set_frequency(freq_table[0]); break;
		case SDL_SCANCODE_S: _gen.set_frequency(freq_table[1]); break;
		case SDL_SCANCODE_X: _gen.set_frequency(freq_table[2]); break;
		case SDL_SCANCODE_D: _gen.set_frequency(freq_table[3]); break;
		case SDL_SCANCODE_C: _gen.set_frequency(freq_table[4]); break;
		case SDL_SCANCODE_V: _gen.set_frequency(freq_table[5]); break;
		case SDL_SCANCODE_G: _gen.set_frequency(freq_table[6]); break;
		case SDL_SCANCODE_B: _gen.set_frequency(freq_table[7]); break;
		case SDL_SCANCODE_H: _gen.set_frequency(freq_table[8]); break;
		case SDL_SCANCODE_N: _gen.set_frequency(freq_table[9]); break;
		case SDL_SCANCODE_J: _gen.set_frequency(freq_table[10]); break;
		case SDL_SCANCODE_M: _gen.set_frequency(freq_table[11]); break;
		case SDL_SCANCODE_COMMA: _gen.set_frequency(freq_table[12]); break;
		case SDL_SCANCODE_L: _gen.set_frequency(freq_table[13]); break;
		case SDL_SCANCODE_PERIOD: _gen.set_frequency(freq_table[14]); break;

		case SDL_SCANCODE_Q: _gen.set_frequency(freq_table[12]); break;
		case SDL_SCANCODE_2: _gen.set_frequency(freq_table[13]); break;
		case SDL_SCANCODE_W: _gen.set_frequency(freq_table[14]); break;
		case SDL_SCANCODE_3: _gen.set_frequency(freq_table[15]); break;
		case SDL_SCANCODE_E: _gen.set_frequency(freq_table[16]); break;
		case SDL_SCANCODE_R: _gen.set_frequency(freq_table[17]); break;
		case SDL_SCANCODE_5: _gen.set_frequency(freq_table[18]); break;
		case SDL_SCANCODE_T: _gen.set_frequency(freq_table[19]); break;
		case SDL_SCANCODE_6: _gen.set_frequency(freq_table[20]); break;
		case SDL_SCANCODE_Y: _gen.set_frequency(freq_table[21]); break;
		case SDL_SCANCODE_7: _gen.set_frequency(freq_table[22]); break;
		case SDL_SCANCODE_U: _gen.set_frequency(freq_table[23]); break;
		case SDL_SCANCODE_I: _gen.set_frequency(freq_table[24]); break;
		case SDL_SCANCODE_9: _gen.set_frequency(freq_table[25]); break;
		case SDL_SCANCODE_O: _gen.set_frequency(freq_table[26]); break;
		case SDL_SCANCODE_0: _gen.set_frequency(freq_table[27]); break;
		case SDL_SCANCODE_P: _gen.set_frequency(freq_table[28]); break;
		default:
			_volume = 0.;
		}
		break;
	case SDL_KEYUP:
		_volume = 0.;
		break;
	default:
		;
	}

}

void Window::handle_keys(const Uint8 * keys)
{

}

void Window::logic()
{
	while (clk::now() < _next_event)
		;
	_next_event += std::chrono::milliseconds(20);

	size_t samples = AudioDriver::SAMPLING_FREQ * 20 / 1000;
	short data[samples];
	for (unsigned i = 0; i < samples; ++i) {
		data[i] = short( _volume * _gen.next_sample() );
	}

	_adrv.queue(data, samples);

}

void Window::render()
{

}
