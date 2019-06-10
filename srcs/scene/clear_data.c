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

static void	clear_face(void *data)
{
	t_darr	*darr;

	darr = (t_darr*)data;
	darr_clear(darr, NULL);
}

void		clear_models(t_darr *models)
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

void		clear_obj(t_obj *obj)
{
	t_object	*object;
	t_group		*group;
	size_t		i;
	size_t		k;

	if (obj)
	{
		i = -1;
		while (++i < obj->objects.size )
		{
			object = (t_object*)darr_at(&obj->objects, i);
			k = -1;
			while (++k < object->groups.size)
			{
				group = (t_group*)darr_at(&object->groups, k);
				darr_clear(&group->faces, &clear_face);
				free(group->name);
			}
			darr_clear(&object->groups, NULL);
		}
		darr_clear(&obj->mtls, NULL);
		darr_clear(&obj->objects, NULL);
		darr_clear(&obj->v, NULL);
		darr_clear(&obj->vn, NULL);
		darr_clear(&obj->vt, NULL);
	}
}