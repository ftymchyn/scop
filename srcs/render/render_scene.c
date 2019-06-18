#include "scop.h"

void	render_scene(t_scene *scene)
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	render_models(scene);
	render_skybox(scene);
}