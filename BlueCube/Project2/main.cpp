#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "include/SDL.h"

#pragma comment (lib, "SDL/libx86/SDL2.lib")
#pragma comment (lib, "SDL/libx86/SDL2main.lib")

//Finestra pintada en vermell. Dins: cub blau.
SDL_Texture *ship;
SDL_Texture *bala;


int main(int argc, char* args[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	
	
	//SDL_Texture* nau= SDL_CreateRGBSurfaceFrom(renderer , SDL_LoadBMP("nau.bmp");

	SDL_Window *window = SDL_CreateWindow("Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_SHOWN
	);


	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* ship = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("ship.bmp"));
	SDL_Texture* bala = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("bala.bmp"));
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
	SDL_Rect laser[2];

	SDL_RenderFillRect(renderer, &laser[2]);

	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool shoot;
	int cont = 0;
	int exit = 0;
	bool check1 = false, check2 = false, check3 = false, check4 = false, check5 = false;

	while (!exit) {

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_KEYDOWN: {
				if (event.key.repeat == 0) {

					switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						check1 = true;
						break;
					case SDLK_RIGHT:
						check2 = true;
						break;
					case SDLK_UP:
						check3 = true;
						break;
					case SDLK_DOWN:
						check4 = true;
						break;
					case SDLK_ESCAPE:
						exit = 1;
						break;
					case SDLK_SPACE:
						shoot = true;
					
						break;
					default:
						break;
					}
				}
			}
							  break;

			case SDL_KEYUP: {

				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					check1 = false;
					break;
				case SDLK_RIGHT:
					check2 = false;
					break;
				case SDLK_UP:
					check3 = false;
					break;
				case SDLK_DOWN:
					check4 = false;
					break;
				default:
					break;
				}
			}

			default:
				break;
			}

		}


		if (check1 == true) {
			if (rect.x > 0) {
				rect.x -= 10;
			}
		}

		if (check2 == true) {
			if (rect.x < 640 - rect.w) {
				rect.x += 10;
			}
		}

		if (check3 == true) {
			if (rect.y > 0) {
				rect.y -= 10;
			}
		}

		if (check4 == true) {
			if (rect.y < 480 - rect.h) {
				rect.y += 10;
			}
		}
		if (shoot == true) {
			shoot = false;
			laser[cont].x = rect.x + 10;
			laser[cont].y = rect.y + 10;
			laser[cont].w = 30;
			laser[cont].h = 30;
			cont++;
			if (cont >= 2)
				cont = 0;
		}
		for (int i = 0; i < 2; i++){
			laser[i].y -= 5;
			
			}


		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderClear(renderer); //Abans de pintar.

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_RenderCopy(renderer, ship, NULL, &rect);
		//SDL_RenderFillRect(renderer, &rect);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
		

		for (int i = 0; i < 2; i++) {
			SDL_RenderCopy(renderer, bala, NULL, &laser[i]);
		}
		SDL_RenderPresent(renderer);

	}

	SDL_Quit();

	system("pause");
	return EXIT_SUCCESS;
}

