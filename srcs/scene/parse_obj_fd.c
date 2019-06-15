#include "scop.h"

static void		create_object(t_obj *obj, char *name)
{
	t_object	*object;

	ft_printf("  -Loading object \"%s\"\n", name ? name : "undefined");
	object = (t_object*)darr_create_last(&obj->objects);
	if (object)
	{
		object->data = obj;
		darr_init(&object->groups, sizeof(t_group));
	}
}

static t_group	*create_group(t_obj *obj, char *name)
{
	t_group		*result;
	t_object	*object;

	if (obj->objects.size == 0)
		create_object(obj, NULL);
	name = (name ? name : ft_strdup("default"));
	ft_printf("    -parsing material group \"%s\"\n", name);
	object = (t_object*)darr_last(&obj->objects);
	result = (t_group*)darr_create_last(&object->groups);
	if (result)
	{
		result->owner = object;
		result->name = name;
		darr_init(&result->faces, sizeof(t_darr));
	}
	return (result);
}

static void		parse_vertex_attrib(t_darr *buffer, char *data, float *dist)
{
	t_float3	*vec3;
	float		num;
	int			i;

	vec3 = (t_float3*)darr_create_last(buffer);
	i = 0;
	while (i < 3 && (size_t)data > 1)
	{
		(*vec3)[i] = ft_atof(data);
		num = (*vec3)[i];
		*dist = MAX(*dist, num);
		data = ft_strchr(data, ' ') + 1;
		i++;
	}
}

static void		parse_face(t_group *group, char *data)
{
	t_darr		*vertexes;
	t_int3		*ivec3;
	char		*subdata;
	size_t		i;

	vertexes = (t_darr*)darr_create_last(&group->faces);
	darr_init(vertexes, sizeof(t_int3));
	while (data)
	{
		while(data[0] == ' ')
			data++;
		subdata = data;
		i = -1;
		ivec3 = (t_int3*)darr_create_last(vertexes);
		while (++i < 3 && (size_t)subdata > 1)
		{
			(*ivec3)[i] = ft_atoi(subdata);
			subdata = ft_strchr(subdata, '/') + 1;
		}
		data = ft_strchr(data, ' ');
	}
}

void			parse_obj_fd(int fd, t_obj *obj, char *root)
{
	t_group		*group;
	char		*line;

	group = NULL;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strnequ(line, "o ", 2))
			create_object(obj, line + 2);
		else if (ft_strnequ(line, "usemtl ", 7))
			group = create_group(obj, ft_strdup(line + 7));
		else if (ft_strnequ(line, "mtllib ", 7))
			parse_mtl(obj, root, line + 7);
		else if (ft_strnequ(line, "v ", 2))
			parse_vertex_attrib(&obj->v, line + 2, &obj->min_dist);
		else if (ft_strnequ(line, "vt ", 3))
			parse_vertex_attrib(&obj->vt, line + 3, &obj->min_dist);
		else if (ft_strnequ(line, "vn ", 3))
			parse_vertex_attrib(&obj->vn, line + 3, &obj->min_dist);
		else if (ft_strnequ(line, "f ", 2))
			parse_face(
				group ? group : (group = create_group(obj, NULL)), line + 2
			);
		ft_memdel((void**)&line);
	}
}