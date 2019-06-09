#include "scop.h"

static void		push_data(t_mesh *mesh, t_obj *obj, t_int3 **vidxs)
{
	t_float3	*v[3];
	t_float3	*vn[3];
	t_float3	*vt[3];
	size_t		i;

	i = -1;
	while (++i < 3)
	{
		v[i] = (t_float3*)darr_at(obj->buffers[0], vidxs[i]->x);
		vn[i] = (t_float3*)darr_at(obj->buffers[1], vidxs[i]->z);
		vt[i] = (t_float3*)darr_at(obj->buffers[2], vidxs[i]->y);
	}
	i = -1;
	while (++i < 3)
	{
		darr_pushback(&mesh->v, v[i]);
		darr_pushback(&mesh->vn, vn[i]);
		darr_pushback(&mesh->vt, vt[i]);
	}
}

static void		correct_face_indexes(t_obj *obj, t_int3 **vidxs)
{
	size_t	i;
	size_t	k;
	t_int3	*vidx;

	i = 0;
	while (i < 3)
	{
		vidx = vidxs[i];
		k = 0;
		while (k < 3)
		{
			if ((size_t)ABS((*vidx)[k]) >= obj->buffers[k]->size)
				(*vidx)[k] = 0;
			else if ((*vidx)[k] < 0)
				(*vidx)[k] = obj->buffers[k]->size - (*vidx)[k];
			k++;
		}
		i++;
	}
}

static void		prepare_mesh_face(t_mesh *mesh, t_obj *obj, t_darr *fverts)
{
	t_int3		*vidxs[3];
	size_t		i;

	if (fverts && fverts->size >= 3)
	{
		i = 2;
		while(i < fverts->size)
		{
			vidxs[0] = (t_int3*)darr_at(fverts, 0);
			vidxs[1] = (t_int3*)darr_at(fverts, i - 1);
			vidxs[2] = (t_int3*)darr_at(fverts, i);
			correct_face_indexes(obj, vidxs);
			push_data(mesh, obj, vidxs);
			i++;
		}
	}
}

static t_model	create_model_from_obj(t_obj obj)
{
	t_model		result;
	t_mesh		mesh;
	t_facegr	*gr;
	size_t		i;
	size_t		k;

	init_model(&result);
	i = 0;
	while (i < obj.fgroups.size)
	{
		init_mesh(&mesh);
		k = 0;
		gr = (t_facegr*)darr_at(&obj.fgroups, i);
		while (k < gr->faces.size)
		{
			prepare_mesh_face(&mesh, &obj, (t_darr*)darr_at(&gr->faces, k));
			k++;
		}
		generate_buffers(&mesh);
		darr_pushback(&result.meshes, &mesh);
		i++;
	}
	return (result);
}

t_darr			load_models(const char *filename)
{
	t_darr	result;
	t_obj	obj;
	t_model	model;
	int		fd;

	darr_init(&result, sizeof(t_model));
	fd = open(filename, O_RDONLY);
	if ( fd != -1)
	{
		ft_printf( "Read file \"%s\" :\n" );
		obj = parse_obj( fd );
		while (obj.v.size > 1)
		{
			model = create_model_from_obj(obj);
			darr_pushback(&result, &model);
			clear_obj(&obj);
			obj = parse_obj( fd );
		}
		clear_obj(&obj);
		close(fd);
	}
	return (result);
}