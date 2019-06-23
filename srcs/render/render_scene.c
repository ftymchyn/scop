#include "scop.h"

void	render_scene(t_scene *scene)
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	scene->camera.m_view = m_view(&scene->camera);
	render_model(scene);
	render_skybox(scene);
}