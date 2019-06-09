#include "scop.h"

int	handle_dropfile(void *scop, SDL_Event *e)
{
	t_scop *s;
	t_darr models;

	if (scop && e)
	{
		s = (t_scop*)scop;
		if (e->type == SDL_DROPFILE)
		{
			if (ft_strequ(ft_strrchr(e->drop.file, '.'), ".obj"))
			{
				models = load_models(e->drop.file);
				clear_models(&s->scene.models);
				s->scene.models = models;
			}
			else
				ft_putendl("Can parse only *.obj");
			
			SDL_free(e->drop.file);
		}
	}
	return (1);
}