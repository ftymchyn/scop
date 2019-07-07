#include "scop.h"

static void	update_shared_uniforms(t_scop *s)
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
}

static void	update_material_uniforms(t_scop *s, t_material *m)
{
	GLint	u_location;

	u_location = glGetUniformLocation(s->scene.model_shader, "u_mtl.ka");
	glUniform4f(u_location, m->ka.x, m->ka.y, m->ka.z, 1.0f);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_mtl.kd");
	glUniform4f(u_location, m->kd.x, m->kd.y, m->kd.z, 1.0f);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_mtl.ks");
	glUniform4f(u_location, m->ks.x, m->ks.y, m->ks.z, 1.0f);
	u_location = glGetUniformLocation(s->scene.model_shader, "u_mtl.ns");
	glUniform1f(u_location, m->ns);
}

void		render_model(t_scop *s)
{
	t_mesh	*mesh;
	int		i;

	GL_CALL(glUseProgram(s->scene.model_shader));
	update_shared_uniforms(s);
	i = 0;
	while (i < s->scene.model.meshes.size)
	{
		mesh = (t_mesh*)darr_at(&s->scene.model.meshes, i);
		update_material_uniforms(s, darr_at(&s->scene.model.materials, i));
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->v.size);
		glBindVertexArray(0);
		i++;
	}
	GL_CALL(glUseProgram(0));
}