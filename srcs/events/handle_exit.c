#include "scop.h"

int	handle_exit(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		((t_scop*)scop)->running = (e->type != SDL_QUIT);
	}
	return (1);
}