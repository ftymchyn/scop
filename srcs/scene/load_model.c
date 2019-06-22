#include "scop.h"

static void		push_data(t_mesh *mesh, t_obj *buffers, t_int3 **vidxs)
{
	t_float3	recalc_v;
	t_float3	*v[3];
	t_float3	*vn[3];
	t_float3	*vt[3];
	size_t		i;

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
	size_t	i;

	i = 0;
	while (i < 3)
	{
		if ((size_t)ABS(vidxs[i]->x) >= buffers->v.size)
			vidxs[i]->x = 0;
		else if (vidxs[i]->x < 0)
			vidxs[i]->x = buffers->v.size - vidxs[i]->x;
		if ((size_t)ABS(vidxs[i]->y) >= buffers->vt.size)
			vidxs[i]->y = 0;
		else if (vidxs[i]->y < 0)
			vidxs[i]->y = buffers->vt.size - vidxs[i]->y;
		if ((size_t)ABS(vidxs[i]->z) >= buffers->vn.size)
			vidxs[i]->z = 0;
		else if (vidxs[i]->z < 0)
			vidxs[i]->z = buffers->vn.size - vidxs[i]->z;
		i++;
	}
}

static void		fill_mesh(t_mesh *mesh, t_darr *verts, t_obj *buffers)
{
	t_int3		*vidxs[3];
	size_t		i;

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

static void		fill_model(t_model *m, t_object *o, t_darr *mtls)
{
	t_group	*group;
	t_mesh	*mesh;
	size_t	i;
	size_t	k;

	(void)mtls;
	mesh = (t_mesh*)darr_last(&m->meshes);
	i = -1;
	while (++i < o->groups.size)
	{
		group = (t_group*)darr_at(&o->groups, i);

		k = -1;
		while (++k < group->faces.size)
			fill_mesh(mesh, (t_darr*)darr_at(&group->faces, k), o->data);
	}
}

t_model			load_model(const char *filename)
{
	t_model	result;
	t_obj	o;
	char	*root;
	int		fd;
	size_t	i;

	init_model(&result);
	init_obj(&o);
	init_mesh((t_mesh*)darr_create_last(&result.meshes));
	if ((fd = open(filename, O_RDONLY)) != -1)
	{
		ft_printf("\nLoad model from file \"%s\" :\n");
		root = ft_strsub(filename, 0, ft_strrchr(filename, '/') - filename);
		parse_obj_fd(fd, &o, root);
		o.mid_vec = (o.min_p + o.max_p) * 0.5f;
		result.scale /= sqrtf(dot3f(o.min_p - o.max_p, o.min_p - o.max_p));
		i = -1;
		while (++i < o.objects.size)
			fill_model(&result, darr_at(&o.objects, i), &o.mtls);
		generate_buffers((t_mesh*)darr_last(&result.meshes));
		free(root);
	}
	close(fd);
	clear_obj(&o);
	return (result);
}