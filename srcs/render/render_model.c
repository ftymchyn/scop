#include "scop.h"

static void	update_model_shader(t_scene *s)
{
	t_mat4	scale;
	t_mat4	rotate;
	GLint	u_location;

	scale = m_scale(s->model.scale);
	rotate = m_rotmatrix_quat(s->model.q_rotation);
	u_location = glGetUniformLocation(s->model_shader, "model");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, m_mult(&scale, &rotate).d);
	u_location = glGetUniformLocation(s->model_shader, "view");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_view.d);
	u_location = glGetUniformLocation(s->model_shader, "proj");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_proj.d);
}

void		render_model(t_scene *scene)
{
	t_mesh	*mesh;
	int		i;

	GL_CALL(glUseProgram(scene->model_shader));
	update_model_shader(scene);
	i = 0;
	while (i < scene->model.meshes.size)
	{
		mesh = (t_mesh*)darr_at(&scene->model.meshes, i);
		glBindVertexArray(mesh->vao);
		glDrawArrays(GL_TRIANGLES, 0, mesh->v.size);
		glBindVertexArray(0);
		i++;
	}
	GL_CALL(glUseProgram(0));
}