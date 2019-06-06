#include "scop.h"

int	handle_dropfile(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		if (e->type == SDL_DROPFILE)
		{
			if (ft_strequ(ft_strrchr(e->drop.file, '.'), ".obj"))
			{
				t_darr models = load_models(e->drop.file);
				clear_models(&models);
			}
			else
				ft_putendl("Can parse only *.obj");
			
			SDL_free(e->drop.file);
		}
	}
	return (1);
}