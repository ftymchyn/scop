#include "scop.h"

void		loop(t_scop *scop)
{
	scop->running = TRUE;
	scop->scene.m_proj = m_projection(&scop->scene.camera);
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glEnable(GL_MULTISAMPLE));
	while (scop->running)
	{
		SDL_PumpEvents();
		render_scene(&scop->scene);
		SDL_GL_SwapWindow(scop->window);
	}
	clear_models(&scop->scene.models);
}