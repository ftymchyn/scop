#include "scop.h"

static void	clear_material(void *data)
{
	t_material *material;

	if (data)
	{
		material = (t_material*)data;
	}
}

static void	clear_mesh(void *data)
{
	t_mesh *mesh;

	if (data)
	{
		mesh = (t_mesh*)data;
		darr_clear(&mesh->v, NULL);
		darr_clear(&mesh->vn, NULL);
		darr_clear(&mesh->vt, NULL);
		GL_CALL(glDeleteBuffers(1, &mesh->vbo_vn));
		GL_CALL(glDeleteBuffers(1, &mesh->vbo_vt));
		GL_CALL(glDeleteBuffers(1, &mesh->vbo_v));
		GL_CALL(glDeleteVertexArrays(1, &mesh->vao));
	}
}

void	clear_models(t_darr *models)
{
	t_model	*model;
	size_t	i;

	i = 0;
	while (i < models->size)
	{
		model = (t_model*)darr_at(models, i);
		darr_clear(&model->materials, &clear_material);
		darr_clear(&model->meshes, &clear_mesh);
		i++;
	}
	darr_clear(models, NULL);
}