/*
 * main.cc
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "Window.h"


int main(int, char **)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	try {
		Window w;

		w.main_loop();

	} catch (const std::exception & e) {
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "Что-то пошло совсем не так..." << std::endl;
		return 2;
	}

	return 0;
}


