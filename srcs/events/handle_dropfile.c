#include "scop.h"

int	handle_dropfile(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		if (e->type == SDL_DROPFILE)
		{
			ft_putendl(e->drop.file);
			SDL_free(e->drop.file);
		}
	}
	return (1);
}