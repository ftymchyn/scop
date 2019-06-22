#include "scop.h"

static void	clear_face(void *data)
{
	t_darr	*darr;

	darr = (t_darr*)data;
	darr_clear(darr, NULL);
}

void		clear_model(t_model *model)
{
	t_mesh		*mesh;
	t_material	*material;
	int			i;

	i = -1;
	while (++i < model->meshes.size)
	{
		mesh = (t_mesh*)darr_at(&model->meshes, i);
		darr_clear(&mesh->v, NULL);
		darr_clear(&mesh->vn, NULL);
		darr_clear(&mesh->vt, NULL);
		GL_CALL(glDeleteBuffers(1, &mesh->vbo_vn));
		GL_CALL(glDeleteBuffers(1, &mesh->vbo_vt));
		GL_CALL(glDeleteBuffers(1, &mesh->vbo_v));
		GL_CALL(glDeleteVertexArrays(1, &mesh->vao));
	}
	darr_clear(&model->meshes, NULL);
	i = -1;
	while (++i < model->materials.size)
	{
		material = (t_material*)darr_at(&model->materials, i);
		ft_memdel((void**)&material->id);
	}
	darr_clear(&model->materials, NULL);
}

void		clear_obj(t_obj *obj)
{
	t_object	*object;
	t_group		*group;
	int			i;
	int			k;

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