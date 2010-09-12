#ifndef main_h
#define main_h


void handle_event(SDL_Surface *screen, SDL_Event *event, layout **layout);
void handle_mouse_down(SDL_Surface *screen, SDL_Event *event, layout **l);
void handle_key_down(SDL_Surface *screen, SDLMod mod, SDLKey key, layout **l);
void redraw(SDL_Surface *screen, layout **l);

#endif
