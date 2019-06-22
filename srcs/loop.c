#include "scop.h"

void		loop(t_scop *scop)
{
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glEnable(GL_MULTISAMPLE));
	while (scop->events.should_close == FALSE)
	{
		SDL_PumpEvents();
		render_scene(&scop->scene);
		SDL_GL_SwapWindow(scop->window);
	}
	clear_model(&scop->scene.model);
}