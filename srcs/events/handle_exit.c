#include "scop.h"

int	handle_exit(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		if ( e->type == SDL_QUIT)
		{
			((t_scop*)scop)->events.should_close = TRUE;
		}
	}
	return (1);
}