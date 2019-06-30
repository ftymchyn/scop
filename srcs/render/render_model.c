#include "scop.h"

static void	update_model_shader(t_scop *s)
{
	t_mat4	model;
	t_mat4	proj;
	GLint	u_location;

	model = m_mult(
		m_scale(s->scene.model.scale),
		m_rotmatrix_quat(s->scene.model.q_rotation)
	);
	proj = (s->events.is_ortho_projection ?
			s->scene.camera.m_ortho : s->scene.camera.m_persp);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_mvp.model");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, model.d);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_mvp.view");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->scene.camera.m_view.d);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_mvp.proj");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, proj.d);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_light.dir");
	glUniform3fv(u_location, 1, (GLfloat*)&s->scene.light.dir);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_light.ka");
	glUniform4f(u_location,
		s->scene.light.ka.x, s->scene.light.ka.y, s->scene.light.ka.z, 1.0f);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_light.kd");
	glUniform4f(u_location,
		s->scene.light.kd.x, s->scene.light.kd.y, s->scene.light.kd.z, 1.0f);
}

void		render_model(t_scop *s)
{
	t_mesh	*mesh;
	int		i;

	GL_CALL(glUseProgram(s->scene.model_shader));
	update_model_shader(s);
	i = 0;
	while (i < s->scene.model.meshes.size)
	{
		mesh = (t_mesh*)darr_at(&s->scene.model.meshes, i);
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->v.size);
		glBindVertexArray(0);
		i++;
	}
	GL_CALL(glUseProgram(0));
}