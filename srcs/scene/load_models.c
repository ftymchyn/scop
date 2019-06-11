#include "scop.h"

static void		push_data(t_mesh *mesh, t_obj *buffers, t_int3 **vidxs)
{
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
		darr_pushback(&mesh->v, v[i]);
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

static void		prepare_mesh_face(t_mesh *mesh, t_darr *verts, t_obj *buffers)
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

static void	create_model(t_model *m, t_object *o, char *root)
{
	t_group	*group;
	t_darr	*face_verts;
	t_mesh	*mesh;
	size_t	i;
	size_t	k;

	(void)root;
	init_model(m);
	i = -1;
	while (++i < o->groups.size)
	{
		group = (t_group*)darr_at(&o->groups, i);
		mesh = (t_mesh*)darr_create_last(&m->meshes);
		init_mesh(mesh);
		k = -1;
		while (++k < group->faces.size)
		{
			face_verts = (t_darr*)darr_at(&group->faces, k);
			prepare_mesh_face(mesh, face_verts, o->data);
		}
		generate_buffers(mesh);
	}
}

t_darr			load_models(const char *filename)
{
	t_darr	result;
	t_obj	obj;
	char	*root;
	int		fd;
	size_t	i;

	darr_init(&result, sizeof(t_model));
	fd = open(filename, O_RDONLY);
	if ( fd != -1)
	{
		ft_printf("\nLoad models from file \"%s\" :\n");
		root = ft_strsub(filename, 0, ft_strrchr(filename, '/') - filename);
		init_obj(&obj);
		parse_obj_fd(fd, &obj, root);
		close(fd);
		i = -1;
		while (++i < obj.objects.size)
		{
			create_model(
				darr_create_last(&result), darr_at(&obj.objects, i), root
			);
		}
		clear_obj(&obj);
		free(root);
	}
	return (result);
}