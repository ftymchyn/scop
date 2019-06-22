#include "scop.h"

void	init_obj(t_obj *obj)
{
	if (obj)
	{
		ft_bzero(obj, sizeof(t_obj));
		darr_init(&obj->v, sizeof(t_float3));
		darr_init(&obj->vn, sizeof(t_float3));
		darr_init(&obj->vt, sizeof(t_float3));
		darr_create_last(&obj->v);
		darr_create_last(&obj->vn);
		darr_create_last(&obj->vt);
		darr_init(&obj->mtls, sizeof(t_mtl));
		darr_init(&obj->objects, sizeof(t_object));
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
		model->q_rotation.w = 1.0f;
		model->scale = 1.0f;
	}
}