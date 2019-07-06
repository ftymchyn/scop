#include "scop.h"

static void		push_data(t_mesh *mesh, t_obj *buffers, t_int3 **vidxs)
{
	t_float3	recalc_v;
	t_float3	*v[3];
	t_float3	*vn[3];
	t_float3	*vt[3];
	int			i;

	i = -1;
	while (++i < 3)
	{
		v[i] = (t_float3*)darr_at(&buffers->v, vidxs[i]->x);
		vt[i] = (t_float3*)darr_at(&buffers->vt, vidxs[i]->y);
		vn[i] = (t_float3*)darr_at(&buffers->vn, vidxs[i]->z);
	}
	if (!vidxs[0]->z || !vidxs[1]->z || !vidxs[2]->z)
		generate_normals(v, vn);
	i = -1;
	while (++i < 3)
	{
		recalc_v = *(v[i]) - buffers->mid_vec;
		darr_pushback(&mesh->v, &recalc_v);
		darr_pushback(&mesh->vn, vn[i]);
		darr_pushback(&mesh->vt, vt[i]);
	}
}

static void		correct_face_indexes(t_obj *buffers, t_int3 **vidxs)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ABS(vidxs[i]->x) >= buffers->v.size)
			vidxs[i]->x = 0;
		else if (vidxs[i]->x < 0)
			vidxs[i]->x = buffers->v.size - vidxs[i]->x;
		if (ABS(vidxs[i]->y) >= buffers->vt.size)
			vidxs[i]->y = 0;
		else if (vidxs[i]->y < 0)
			vidxs[i]->y = buffers->vt.size - vidxs[i]->y;
		if (ABS(vidxs[i]->z) >= buffers->vn.size)
			vidxs[i]->z = 0;
		else if (vidxs[i]->z < 0)
			vidxs[i]->z = buffers->vn.size - vidxs[i]->z;
		i++;
	}
}

static void		fill_mesh(t_mesh *mesh, t_darr *verts, t_obj *buffers)
{
	t_int3	*vidxs[3];
	int		i;

	if (verts->size >= 3)
	{
		i = 2;
		while(i < verts->size)
		{
			vidxs[0] = (t_int3*)darr_at(verts, 0);
			vidxs[1] = (t_int3*)darr_at(verts, i - 1);
			vidxs[2] = (t_int3*)darr_at(verts, i);
			correct_face_indexes(buffers, vidxs);
			push_data(mesh, buffers, vidxs);
			i++;
		}
	}
}

static void		fill_material(t_material *mat, t_mtl *mtl)
{
	init_material(mat);
	mat->id = ft_strdup(mtl->name);
	mat->ka = mtl->ka;
	mat->kd = mtl->kd;
	mat->ks = mtl->ks;
	mat->ns = mtl->ns;
}

static t_mesh	*get_material_mesh(t_model *m, t_darr *mtls, const char *mtl_id)
{
	t_mesh		*result;
	int			i;

	result = NULL;
	i = -1;
	while (!result && ++i < m->materials.size)
	{
		if (ft_strequ(((t_material*)darr_at(&m->materials, i))->id, mtl_id))
			result = (t_mesh*)darr_at(&m->meshes, i);
	}
	i = -1;
	while (!result && ++i < mtls->size)
	{
		if (ft_strequ(((t_mtl*)darr_at(mtls, i))->name, mtl_id))
		{
			fill_material(darr_create_last(&m->materials), darr_at(mtls, i));
			result = (t_mesh*)darr_create_last(&m->meshes);
			init_mesh(result);
		}
	}
	if (result == NULL)
		result = (t_mesh*)darr_at(&m->meshes, 0);
	return (result);
}

static void		fill_model_from_obj(t_model *m, t_obj *o)
{
	t_object	*obj;
	t_group		*group;
	t_mesh		*mesh;
	int			i[3];

	init_material(darr_create_last(&m->materials));
	init_mesh(darr_create_last(&m->meshes));
	i[0] = -1;
	while (++i[0] < o->objects.size)
	{
		obj = (t_object*)darr_at(&o->objects, i[0]);
		i[1] = -1;
		while (++i[1] < obj->groups.size)
		{
			group = (t_group*)darr_at(&obj->groups, i[1]);
			mesh = get_material_mesh(m, &o->mtls, group->name);
			i[2] = -1;
			while (++i[2] < group->faces.size)
			{
				fill_mesh(mesh, darr_at(&group->faces, i[2]), o);
			}
		}
	}
}

t_model			load_model(const char *filename)
{
	t_model	result;
	t_obj	o;
	char	*root;
	int		fd;

	init_model(&result);
	init_obj(&o);
	if ((fd = open(filename, O_RDONLY)) != -1)
	{
		root = ft_strsub(filename, 0, ft_strrchr(filename, '/') - filename + 1);
		parse_obj_fd(fd, &o, root);
		o.mid_vec = (o.min_p + o.max_p) * 0.5f;
		result.scale /= sqrtf(dot3f(o.min_p - o.max_p, o.min_p - o.max_p));
		fill_model_from_obj(&result, &o);
		darr_foreach(&result.meshes, (void (*)(void*))&generate_buffers);
		free(root);
	}
	close(fd);
	clear_obj(&o);
	return (result);
}