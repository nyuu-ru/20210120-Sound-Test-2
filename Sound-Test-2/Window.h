/*
 * Window.h
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>
#include <memory>
#include <chrono>

#include "AudioDriver.h"
#include "Generator.h"

class Window
{
protected:
	using clk = std::chrono::high_resolution_clock;

	std::shared_ptr<SDL_Window> _window;
	std::shared_ptr<SDL_Renderer> _renderer;

	AudioDriver _adrv;
	SquareWaveGenerator _gen;

	clk::time_point _next_event;

	double _volume { 0. };

public:
	Window();

	void main_loop();

	void handle_event(const SDL_Event & event);
	void handle_keys(const Uint8 * keys);
	void logic();
	void render();
};



#endif /* WINDOW_H_ */
