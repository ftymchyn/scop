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
	t_facegr	*facegr;
	size_t		i;

	if (obj)
	{
		darr_clear( &obj->v, NULL );
		darr_clear( &obj->vn, NULL );
		darr_clear( &obj->vt, NULL );
		i = 0;
		while (i < obj->fgroups.size )
		{
			facegr = (t_facegr*)darr_at(&obj->fgroups, i);
			darr_clear(&facegr->faces, &clear_face);
			i++;
		}
		darr_clear(&obj->fgroups, NULL);
	}
}