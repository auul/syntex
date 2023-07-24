#include <syntex.h>

#include <SDL2/SDL.h>

#define SDL_INIT_FLAGS (SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS)
#define SDL_WIN_FLAGS (SDL_WINDOW_RESIZABLE)
#define SDL_RENDER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)

SDL_Window *  win;
SDL_Renderer *render;
bool          win_redraw, win_run;

bool WinExit(void)
{
	if (render) {
		SDL_DestroyRenderer(render);
		render = NULL;
	}

	if (win) {
		SDL_DestroyWindow(win);
		win = NULL;
	}

	SDL_Quit();

	return false;
}

bool WinInit(void)
{
	if (SDL_Init(SDL_INIT_FLAGS) != 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return WinExit();
	}

	win = SDL_CreateWindow(WIN_INIT_TITLE,
	                       SDL_WINDOWPOS_UNDEFINED,
	                       SDL_WINDOWPOS_UNDEFINED,
	                       WIN_INIT_WIDTH,
	                       WIN_INIT_HEIGHT,
	                       SDL_WIN_FLAGS);
	if (!win) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return WinExit();
	}

	render = SDL_CreateRenderer(win, -1, SDL_RENDER_FLAGS);
	if (!render) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return WinExit();
	}

	return true;
}

void WinDraw(void)
{
	SDL_SetRenderDrawColor(render, SplitRGBA(WIN_BG_RGB));
	SDL_RenderClear(render);

	SDL_RenderPresent(render);
	win_redraw = false;
}

void WinEvent(SDL_Event *e)
{
	switch (e->type) {
	case SDL_QUIT:
		win_run = false;
		break;
	case SDL_WINDOWEVENT:
		win_redraw = true;
		break;
	}
}

void WinLoop(void)
{
	SDL_Event e;

	win_redraw = true;

	for (win_run = true; win_run;) {
		if (win_redraw) {
			WinDraw();
		}

		while (SDL_PollEvent(&e)) {
			WinEvent(&e);
		}
	}
}
