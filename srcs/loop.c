#include "scop.h"

static void	render_model(void *data)
{
	t_model	*model;
	t_mesh	*mesh;
	size_t	i;

	model = (t_model*)data;
	i = 0;
	while (i < model->meshes.size)
	{
		mesh = (t_mesh*)darr_at(&model->meshes, i);
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->v.size);
		glBindVertexArray(0);
		i++;
	}
}

void		loop(t_scop *scop)
{
	scop->running = TRUE;
	GLuint program = create_shader_program( "srcs/shaders/model.glsl");

	while (scop->running)
	{
		SDL_PumpEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		darr_foreach(&scop->scene.models, &render_model);
		glUseProgram(0);
		SDL_GL_SwapWindow(scop->window);
	}
	clear_models(&scop->scene.models);
}