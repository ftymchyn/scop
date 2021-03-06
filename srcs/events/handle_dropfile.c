#include "scop.h"

int	handle_dropfile(void *scop, SDL_Event *e)
{
	t_scop	*s;
	t_model	model;

	if (scop && e)
	{
		s = (t_scop*)scop;
		if (e->type == SDL_DROPFILE)
		{
			if (ft_strequ(ft_strrchr(e->drop.file, '.'), ".obj"))
			{
				model = load_model(e->drop.file);
				clear_model(&s->scene.model);
				s->scene.model = model;
			}
			else
				ft_putendl("Can parse only *.obj");
			
			SDL_free(e->drop.file);
		}
	}
	return (1);
}