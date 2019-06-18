#include "scop.h"

static void	draw_model(void *data)
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

static void	update_model_shader(t_scene *s)
{
	GLint u_location;

	u_location = glGetUniformLocation(s->model_shader, "model");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_model.d);
	u_location = glGetUniformLocation(s->model_shader, "view");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_view.d);
	u_location = glGetUniformLocation(s->model_shader, "proj");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->m_proj.d);
}

void		render_models(t_scene *scene)
{
	GL_CALL(glUseProgram(scene->model_shader));
	update_model_shader(scene);
	darr_foreach(&scene->models, &draw_model);
	GL_CALL(glUseProgram(0));
}