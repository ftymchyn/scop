#include "scop.h"

void	prepare_mat4_uniforms(GLuint program, t_scene *s)
{
	GLint u_location;

	u_location = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_model.d);
	u_location = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_view.d);
	u_location = glGetUniformLocation(program, "proj");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_proj.d);
}

void	render_scene(t_scene *scene)
{
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CALL(glUseProgram(scene->model_shader));
	prepare_mat4_uniforms(scene->model_shader, scene);
	render_model(&scene->models);
	GL_CALL(glUseProgram(0));
}