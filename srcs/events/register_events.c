#include "scop.h"

void	register_events(t_scop *scop)
{
	SDL_AddEventWatch(&handle_exit, (void*)scop);
	SDL_AddEventWatch(&handle_keyboard, (void*)scop);
	SDL_AddEventWatch(&handle_dropfile, (void*)scop);
}