#include "scop.h"

void	render_scene(t_scene *scene)
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CALL(glUseProgram(scene->model_shader));
	render_model(&scene->models);
	GL_CALL(glUseProgram(0));
}