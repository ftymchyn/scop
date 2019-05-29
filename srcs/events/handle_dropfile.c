#include "scop.h"

static void		clear_face(void *data)
{
	t_darr	*darr;

	darr = (t_darr*)data;
	darr_clear(darr, NULL);
}

int	handle_dropfile(void *scop, SDL_Event *e)
{
	if (scop && e)
	{
		if (e->type == SDL_DROPFILE)
		{
			if (ft_strequ(ft_strrchr(e->drop.file, '.'), ".obj"))
			{
				t_obj o = parse_obj(e->drop.file);

				darr_clear( &o.v, NULL );
				darr_clear( &o.vn, NULL );
				darr_clear( &o.vt, NULL );
				darr_clear( &o.f, &clear_face );
			}
			else
				ft_putendl("Can parse only *.obj");
			
			SDL_free(e->drop.file);
		}
	}
	return (1);
}