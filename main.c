#include <stdlib.h>
#include "SDL.h"
#include "layout.h"
#include "main.h"
#include "SDL_gfxPrimitives.h"

int draw_rect(SDL_Surface *dst, rect *r, unsigned int color)
{
	return rectangleColor(dst, 
	                      r->left->start->x + 1,
	                      r->top->start->y + 1,
	                      r->right->start->x - 1,
	                      r->bottom->start->y - 1,
	                      color);
}

int draw_all_rects(SDL_Surface *dst, rect_list *l, unsigned int color)
{
	while (l) {
		draw_rect(dst, l->current, color);
		l = l->next;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
	
	SDL_Surface *screen;
	
	screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if ( screen == NULL ) {
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		exit(1);
	}
	
	rect_list *rects = malloc(sizeof(rect_list));
	rects->current = make_layout(make_point(640, 480));
	rects->next = NULL;
	
	
	SDL_Event event;
	
	while (1) {
		if (SDL_WaitEvent(&event))
			do {
				handle_event(screen, &event, &rects);
			} while (SDL_PollEvent(&event));
	}
}


void handle_event(SDL_Surface *screen, SDL_Event *event, layout **layout)
{
	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			handle_mouse_down(screen, event, layout);
			break;
		case SDL_KEYDOWN:
			handle_key_down(screen, event->key.keysym.mod, 
			                event->key.keysym.sym, 
			                layout);
			break;
		case SDL_QUIT:
			exit(0);
	}
}


void handle_mouse_down(SDL_Surface *screen, SDL_Event *event, layout **l)
{
	point *p = make_point(event->button.x, event->button.y);
	rect *r = find_rect_containing(*l, p);
	if (r == NULL)
		return;
	switch (event->button.button) {
		case 1:
			split_rect_vertically(l, r, p);
			break;
		case 3:
			split_rect_horizontally(l, r, p);
	}
	redraw(screen, l);
}


void handle_key_down(SDL_Surface *screen, SDLMod mod, SDLKey key, layout **l)
{
	switch (key) {
		case SDLK_ESCAPE:
			exit(0);
			break;
		default:
			break;
	}
}


void redraw(SDL_Surface *screen, layout **l)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB( screen->format, 0,0,0));
	draw_all_rects(screen, *l, 0x008888FF);
	SDL_Flip(screen);
}
