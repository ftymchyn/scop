#include "scop.h"

static void		clear_str(void *data)
{
	free(*(char**)data);
}

static void		parse_f(t_obj *obj, t_darr *strvec)
{
	size_t		i;
	size_t		j;
	t_darr		fdata;
	t_int3		vdata;
	char		*str;

	i = 1;
	darr_init(&fdata, sizeof(t_int3));
	str = NULL;
	while (i < darr_size(strvec))
	{
		str = *(char**)darr_at(strvec, i);
		j = 0;
		while (j < 3)
		{
			vdata[j] = ft_atoi(str);
			str = ft_strchr(str, '/') + 1;
			j++;
			if (str == (char*)1)
				break ;
		}
		darr_pushback(&fdata, &vdata);
		i++;
	}
	if (darr_size(&fdata) > 0)
		darr_pushback(&obj->f, &fdata);
}

static void	parse_vatrrib(t_obj *obj, char *type, t_darr *strvec)
{
	t_float3	result;

	result.xyz = 0.0f;
	if (darr_size(strvec) >= 3)
	{
		result.x = ft_atof(*(char**)darr_at(strvec, 1));
		result.y = ft_atof(*(char**)darr_at(strvec, 2));
		if (darr_size(strvec) >= 4)
			result.z = ft_atof(*(char**)darr_at(strvec, 3));
	}
	if (ft_strequ(type, "v"))
		darr_pushback(&obj->v, &result);
	else if (ft_strequ(type, "vn"))
		darr_pushback(&obj->vn, &result);
	else if (ft_strequ(type, "vt"))
		darr_pushback(&obj->vt, &result);
}

static void		parse_obj_line(const char *name, const char *line, t_obj *obj)
{
	t_darr		strvec;
	char		*type;

	strvec = ft_strsplit_vec(line, ' ');
	type = NULL;
	if (darr_size(&strvec) > 0)
	{
		type = *(char**)darr_at(&strvec, 0);
		if (ft_strequ(type, "f"))
			parse_f(obj, &strvec);
		else
			parse_vatrrib(obj, type, &strvec);
	}
	ft_dprintf(
		2,
		"\r -load object \"%s\" -> V[%d] VN[%d] VT[%d] FACES[%d] ",
		name,
		darr_size(&obj->v),
		darr_size(&obj->vn),
		darr_size(&obj->vt),
		darr_size(&obj->f)
	);
	darr_clear(&strvec, &clear_str);
}

t_obj			parse_obj(int fd)
{
	static char	*obj_name = NULL;
	static char	*line = NULL;
	t_obj		result;

	darr_init(&result.v, sizeof(t_float3));
	darr_init(&result.vn, sizeof(t_float3));
	darr_init(&result.vt, sizeof(t_float2));
	darr_init(&result.f, sizeof(t_darr));
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'o')
		{
			ft_memdel((void**)&obj_name);
			obj_name = ft_strjoin(line + 2, NULL);
			if (darr_size(&result.f) > 0)
				break ;
		}
		else
			parse_obj_line(obj_name, line, &result);
		ft_memdel((void**)&line);
	}
	ft_dprintf(2, "DONE\n");
	ft_memdel((void**)&line);
	return (result);
}