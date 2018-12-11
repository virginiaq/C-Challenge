#define SDL_MAIN_HANDLED
#include "blackcolor.h"
#include <SDL.h>

int main(int argc, char **argv)
{
	int ret = 0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		ret = -1;
		goto endmain;
	}

	SDL_Window *window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
	if (!window)
	{
		SDL_Log("unable to create window: %s", SDL_GetError());
		ret = -1;
		goto sdlquit;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("unable to create renderer: %s", SDL_GetError());
		ret = -1;
		goto closewindow;
	}
	int j;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	uint32_t *bgpixels;
	SDL_Texture *background = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 20, 20);

	SDL_LockTexture(background, NULL, (void **)(&bgpixels), &j);

	for (int i = 0; i < 255; i++)
	{
		bgpixels[i] = black;
		black +=increment;
	}

	SDL_UnlockTexture(background);

	for (;;)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto closerendered;
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background, &(SDL_Rect){1, 1, 2, 2}, NULL);

		SDL_RenderPresent(renderer);
	}

closerendered:
	SDL_DestroyRenderer(renderer);
closewindow:
	SDL_DestroyWindow(window);
sdlquit:
	SDL_Quit();
endmain:
	return ret;
}
