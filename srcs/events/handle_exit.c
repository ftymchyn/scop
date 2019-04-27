#include "scop.h"

int	handle_events(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		((t_scop*)scop)->running = (e->type == SDL_QUIT);
	}
	return (1);
}