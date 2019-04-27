#include "scop.h"

int	handle_keyboard(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_ESCAPE)
		{
			((t_scop*)scop)->running = FALSE;
		}
	}
	return (1);
}