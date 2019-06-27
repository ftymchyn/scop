#include "scop.h"

void	render_scene(t_scop *s)
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	s->scene.camera.m_view = m_view(&s->scene.camera);
	render_model(s);
	render_skybox(s);
}