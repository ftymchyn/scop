#include "scop.h"

void	init_obj(t_obj *obj)
{
	t_float3 tmp;

	tmp.xyz = 0.0f;
	if (obj)
	{
		ft_bzero(obj, sizeof(t_obj));
		darr_init(&obj->v, sizeof(t_float3));
		darr_init(&obj->vn, sizeof(t_float3));
		darr_init(&obj->vt, sizeof(t_float3));
		darr_pushback(&obj->v, &tmp);
		darr_pushback(&obj->vn, &tmp);
		darr_pushback(&obj->vt, &tmp);
		darr_init(&obj->fgroups, sizeof(t_facegr));
		darr_init(&obj->gr.faces, sizeof(t_darr));
		obj->buffers[0] = &obj->v;
		obj->buffers[1] = &obj->vn;
		obj->buffers[2] = &obj->vt;
	}
}

void	init_mesh(t_mesh *mesh)
{
	if (mesh)
	{
		ft_bzero(mesh, sizeof(t_mesh));
		darr_init(&mesh->v, sizeof(t_float3));
		darr_init(&mesh->vn, sizeof(t_float3));
		darr_init(&mesh->vt, sizeof(t_float2));
	}
}

void	init_model(t_model *model)
{
	if (model)
	{
		ft_bzero(model, sizeof(t_model));
		darr_init(&model->materials, sizeof(t_material));
		darr_init(&model->meshes, sizeof(t_mesh));
	}
}