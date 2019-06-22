#include "scop.h"

void		loop(t_scop *scop)
{
	scop->scene.m_view = m_view(&scop->scene.camera);
	scop->scene.m_proj = m_projection(&scop->scene.camera);
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