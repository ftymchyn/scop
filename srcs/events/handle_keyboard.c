#include "scop.h"

int	handle_keyboard(void *scop, SDL_Event *e)
{
	t_events	*events;

	if (scop && e)
	{
		events = &((t_scop*)scop)->events;
		if (e->type == SDL_KEYUP)
		{
			if (e->key.keysym.sym == SDLK_ESCAPE)
				events->should_close = TRUE;
			else if (e->key.keysym.sym == SDLK_KP_5)
			{
				events->is_ortho_projection = !events->is_ortho_projection;
				((t_scop*)scop)->scene.camera.pos.z +=
					(events->is_ortho_projection ? 1.0f : -1.0f);
			}
		}
	}
	return (1);
}