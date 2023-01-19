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

void first() {

}
float getY(int f, int xd, float p, int Cma, float k, float l) {
	float h;
	h = l * pow(((float)Cma / xd) * f, 2) + (((float)Cma / xd)* f) * k + p;
	return h;
}



int main() {
	int height = 800;
	int width = 800;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Quadratic Functions", 100, 100, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer *s = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(s, SDL_BLENDMODE_BLEND);
	float graph[width + 1][height + 1];
	float Hheight = (float)height / 2;
	float Hwidth = (float)width / 2;
	float CMax = 10;

	float a1 = 1;
	float b = 1.23;
	float c = (float)0.12103;
	while (1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
			return 0;
			}
		}

		SDL_RenderClear(s);
		for (int i = 0; i <= width; i++) {
			for (int a = 0; a <= height; a++) {
				graph[i][a] = 0;
			}
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
			for (int a = -Hheight; a < Hheight; a++) {
				if (fabsf((((float)CMax / Hheight) * a) - getY(i, Hwidth, c, CMax, b, a1)) < fabsf((((float)CMax / Hheight) * (a - 1)) - getY(i, Hwidth, c, CMax, b, a1)) && fabsf((((float)CMax / Hheight) * a) - getY(i, Hwidth, c, CMax, b, a1)) < fabs((((float)CMax / Hheight) * (a + 1)) - getY(i, Hwidth, c, CMax, b, a1)) || fabsf((((float)CMax / Hheight) * a) - getY(i, Hwidth, c, CMax, b, a1)) < fabsf((((float)CMax / Hheight) * a) - getY(i - 1, Hwidth, c, CMax, b, a1)) && fabsf((((float)CMax / Hheight) * a) - getY(i, Hwidth, c, CMax, b, a1)) < fabsf((((float)CMax / Hheight) * a) - getY(i + 1, Hwidth, c, CMax, b, a1))) {
					if (getY(i + 1, Hwidth, c, CMax, b, a1) > getY(i, Hwidth, c, CMax, b, a1) && getY(i, Hwidth, c, CMax, b, a1) < getY(i - 1, Hwidth, c, CMax, b, a1) || getY(i + 1, Hwidth, c, CMax, b, a1) < getY(i, Hwidth, c, CMax, b, a1) && getY(i, Hwidth, c, CMax, b, a1) > getY(i - 1, Hwidth, c, CMax, b, a1)) {
						if (fabsf((((float)CMax / Hheight) * a) - getY(i, Hwidth, c, CMax, b, a1)) < fabsf((((float)CMax / Hheight) * (a - 1)) - getY(i, Hwidth, c, CMax, b, a1)) && fabsf((((float)CMax / Hheight) * a) - getY(i, Hwidth, c, CMax, b, a1)) < fabs((((float)CMax / Hheight) * (a + 1)) - getY(i, Hwidth, c, CMax, b, a1))) {
							graph[i + (int)Hwidth][a + (int)Hheight] = 1;
							SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, 0xFF);
							SDL_RenderDrawPoint(s, i + Hwidth, Hheight - a);
							SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
						}
					} else {
						graph[i + (int)Hwidth][a + (int)Hheight] = 1;
						SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, 0xFF);
						SDL_RenderDrawPoint(s, i + Hwidth, Hheight - a);
						SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
					}
				}
			}
		}
		for (int c = 0; c < 4; c++) {
			for (int i = 1; i < width; i++) {
				for (int a = 1; a < height; a++) {
					if (graph[i][a] != 1) {
						float fade;
						fade = (float)(graph[i + 1][a] + graph[i - 1][a] + graph[i][a + 1] + graph[i][a - 1]) / 4;
						if (fade > 0.2) {
							SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, fade * 100);
							SDL_RenderDrawPoint(s, i, height - a);
							SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
						}
						graph[i][a] = fade;
					}
				}
			}
			for (int a = 1; a < height; a++) {
				for (int i = width - 1; i >= 1; i--) {
					if (graph[i][a] != 1) {
						float fade;
						fade = (float)(graph[i + 1][a] + graph[i - 1][a] + graph[i][a + 1] + graph[i][a - 1]) / 4;
						if (fade > 0.2) {
							SDL_SetRenderDrawColor(s, 0x59, 0x5f, 0xFF, fade * 100);
							SDL_RenderDrawPoint(s, i, height - a);
							SDL_SetRenderDrawColor(s, 0x00, 0x00, 0x00, 0xFF);
						}
						graph[i][a] = fade;
					}
				}
			}

		}
		SDL_RenderPresent(s);
	}
}
