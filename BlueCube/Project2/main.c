#include <stdlib.h>
#include <stdio.h>
#include "include/SDL.h"

#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")

//Finestra pintada en vermell. Dins: cub blau.

int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Window",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640, 480,
			SDL_WINDOW_SHOWN
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderClear(renderer); //Abans de pintar.

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_Rect rect;
		rect.x = 300;
		rect.y = 220;
		rect.w = 40;
		rect.h = 40;

		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer); //Al final d'acabar totes les operacions de pintat.

		//Ara analitzo input.

		SDL_Event event;
		int exit = 0;
		
		while (!exit) {

			while (SDL_PollEvent(&event)) {

				switch (event.type) {

				case SDL_KEYDOWN: {
					if (event.key.repeat == 0) {

						switch (event.key.keysym.sym) {
						case SDLK_LEFT:
							while (rect.x > 0) {
								rect.x -= 10;
							}
							break;
						case SDLK_RIGHT:
							if (rect.x < 640 - rect.w) {
								rect.x += 10;
							}
							break;
						case SDLK_UP:
							if (rect.y > 0) {
								rect.y -= 10;
							}
							break;
						case SDLK_DOWN:
							if (rect.y < 480 - rect.h) {
								rect.y += 10;
							}
							break;
						case SDLK_ESCAPE:
							exit = 1;
							break;
						default:
							break;
						}
					}
				}
								  break;
				default:
					break;
				}
			
			
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

			SDL_RenderClear(renderer); //Abans de pintar.

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

			SDL_RenderFillRect(renderer, &rect);

			SDL_RenderPresent(renderer);
		}

	}

	SDL_Quit();

	system("pause");
	return EXIT_SUCCESS;
}

