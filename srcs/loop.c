#include "scop.h"

void		loop(t_scop *scop)
{
	GL_CALL(glEnable(GL_DEPTH_TEST));
	GL_CALL(glEnable(GL_MULTISAMPLE));
	scop->scene.skybox = create_skybox("res/skybox/");
	scop->scene.model_shader = create_shader_program(
		"srcs/shaders/model.glsl"
	);
	init_model(&scop->scene.model);
	while (scop->events.should_close == FALSE)
	{
		SDL_PumpEvents();
		render_scene(scop);
		SDL_GL_SwapWindow(scop->window);
	}
	clear_model(&scop->scene.model);
}