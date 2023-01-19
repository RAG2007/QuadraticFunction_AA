#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <float.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

float getY(int f, int xd, float p, int Cma, float k, float l) {
	float h;
	h = l * pow(((float)Cma / xd) * f, 2) + (((float)Cma / xd) * f) * k + p;
	return h;
}

int main() {
	int height = 800;
	int width = 800;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Quadratic Functions", 100, 100, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(s, SDL_BLENDMODE_BLEND);

	float graph[width + 1][height + 1],
	      Hheight = (float)height / 2,
	      Hwidth = (float)width / 2,
	      CMax = 10;

	float a = 1,
	      b = 1.23,
	      c = (float)0.12103;
	while (1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return 0;
		}

		SDL_RenderClear(s);
		for (int i = 0; i <= width; i++) {
			for (int a = 0; a <= height; a++)
				graph[i][a] = 0;
		}

		for (int i = 0; i < height; i++) {
			SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 255);
			SDL_RenderDrawPoint(s, width / 2, i);
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
			if (i % (int)(Hheight / CMax) == 0) {
				for (int a = 0; a < 5; a++) {
					SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderDrawPoint(s, Hwidth + (a - 2), i);
					SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
				}
			}
		}

		for (int i = 0; i < width; i++) {
			SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderDrawPoint(s, i, Hheight);
			SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
			if (i % (int)(Hwidth / CMax) == 0) {
				for (int a = 0; a < 5; a++) {
					SDL_SetRenderDrawColor(s, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderDrawPoint(s, i, Hheight + (a - 2));
					SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
				}
			}
		}
		for (int i = -Hwidth; i < Hwidth; i++) {
			float actualh = getY(i, Hwidth, c, CMax, b, a),
			      addrealh = getY(i + 1, Hwidth, c, CMax, b, a),
			      subrealh = getY(i - 1, Hwidth, c, CMax, b, a);
			for (int y = -Hheight; y < Hheight; y++) {
				float nactualh = (((float)CMax / Hheight) * y),
				      addnrealh = (((float)CMax / Hheight) * (y + 1)),
				      subnrealh = (((float)CMax / Hheight) * (y - 1)),
				      ahna = fabsf(actualh - nactualh),
				      ahanrh = fabs(actualh - addnrealh),
				      ahsnrh = fabsf(actualh - subnrealh),
				      nahsh = fabsf(nactualh - subrealh),
				      naharh = fabsf(nactualh - addrealh);

				if ((ahna < ahsnrh && ahna < ahanrh) || (ahna < nahsh && ahna < naharh)) {
					if ((addrealh > actualh && actualh < subrealh) || (addrealh < actualh && actualh > subrealh)) {
						if (ahna < ahsnrh && ahna < ahanrh) {
							graph[i + (int)Hwidth][y + (int)Hheight] = 1;
							SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, 0xFF);
							SDL_RenderDrawPoint(s, i + Hwidth, Hheight - y);
							SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
						}
					} else {
						graph[i + (int)Hwidth][y + (int)Hheight] = 1;
						SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, 0xFF);
						SDL_RenderDrawPoint(s, i + Hwidth, Hheight - y);
						SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
					}
				}
			}
		}

		for (int c = 0; c < 4; c++) {
			for (int i = 1; i < width; i++) {
				for (int j = 1; j < height; j++) {
					if (graph[i][j] != 1) {
						float fade;
						fade = (float)(graph[i + 1][j] + graph[i - 1][j] + graph[i][j + 1] + graph[i][j - 1]) / 4;
						if (fade > 0.2) {
							SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, fade * 100);
							SDL_RenderDrawPoint(s, i, height - j);
							SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
						}
						graph[i][j] = fade;
					}
				}
			}

			for (int j = 1; j < height; j++) {
				for (int i = width - 1; i >= 1; i--) {
					if (graph[i][j] != 1) {
						float fade;
						fade = (float)(graph[i + 1][j] + graph[i - 1][j] + graph[i][j + 1] + graph[i][j - 1]) / 4;
						if (fade > 0.2) {
							SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, fade * 100);
							SDL_RenderDrawPoint(s, i, height - j);
							SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
						}
						graph[i][j] = fade;
					}
				}
			}
		}

		SDL_RenderPresent(s);
	}
}
