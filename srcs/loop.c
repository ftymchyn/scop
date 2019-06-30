#include "scop.h"

static void	init_scene(t_scop *s)
{
	SDL_GetWindowSize(s->window, &s->scene.camera.w, &s->scene.camera.h);
	s->scene.camera.pos = (t_float3){ 0.0f, 0.0f, 1.0f };
	s->scene.camera.q_rotation.w = 1.0f;
	s->scene.camera.m_view = m_view(&s->scene.camera);
	s->scene.camera.m_persp = m_persp(
		s->scene.camera.w, s->scene.camera.h, 0.1f, 100.0f
	);
	s->scene.camera.m_ortho = m_ortho(
		s->scene.camera.w, s->scene.camera.h, 1.0f, 100.0f
	);
	s->scene.skybox = create_skybox("res/skybox/");
	s->scene.model_shader = create_shader_program("srcs/shaders/model.glsl");
}

void		loop(t_scop *scop)
{
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glEnable(GL_MULTISAMPLE));
	init_scene(scop);
	init_model(&scop->scene.model);
	while (scop->events.should_close == FALSE)
	{
		SDL_PumpEvents();
		render_scene(scop);
		SDL_GL_SwapWindow(scop->window);
	}
	clear_model(&scop->scene.model);
}