#include "scop.h"

int	handle_dropfile(void *scop, SDL_Event *e)
{
	t_scop	*s;
	t_darr	models;
	float	min_dist;

	if (scop && e)
	{
		s = (t_scop*)scop;
		if (e->type == SDL_DROPFILE)
		{
			if (ft_strequ(ft_strrchr(e->drop.file, '.'), ".obj"))
			{
				models = load_models(e->drop.file, &min_dist);
				clear_models(&s->scene.models);
				s->scene.models = models;
				s->scene.camera.pos = (t_float3){0.0f, 0.0f, min_dist + 1.0f};
				s->scene.m_view = m_view(&s->scene.camera);
				s->scene.q_rotation = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
				m_identity(&s->scene.m_model);
			}
			else
				ft_putendl("Can parse only *.obj");
			
			SDL_free(e->drop.file);
		}
	}
	return (1);
}