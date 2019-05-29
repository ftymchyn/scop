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
		// TODO : implement atof in libft
		result.x = atof(*(char**)darr_at(strvec, 1));
		result.y = atof(*(char**)darr_at(strvec, 2));
		if (darr_size(strvec) >= 4)
			result.z = atof(*(char**)darr_at(strvec, 3));
	}
	if (ft_strequ(type, "v"))
		darr_pushback(&obj->v, &result);
	else if (ft_strequ(type, "vn"))
		darr_pushback(&obj->vn, &result);
	else if (ft_strequ(type, "vt"))
		darr_pushback(&obj->vt, &result);
}

static void		parse_obj_line(const char *line, t_obj *obj)
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
	ft_putstr_fd("\rv[", 1);
	ft_putnbr_fd(darr_size(&obj->v), 2);
	ft_putstr_fd("] vn[", 1);
	ft_putnbr_fd(darr_size(&obj->vn), 2);
	ft_putstr_fd("] vt[", 1);
	ft_putnbr_fd(darr_size(&obj->vt), 2);
	ft_putstr_fd("] faces: ", 1);
	ft_putnbr_fd(darr_size(&obj->f), 2);
	darr_clear(&strvec, &clear_str);
}

t_obj			parse_obj(const char *filename)
{
	t_obj	result;
	char	*line;
	int		fd;

	darr_init(&result.v, sizeof(t_float3));
	darr_init(&result.vn, sizeof(t_float3));
	darr_init(&result.vt, sizeof(t_float3));
	darr_init(&result.f, sizeof(t_darr));
	line = NULL;
	fd = open(filename, O_RDONLY);
	if ( fd != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			parse_obj_line(line, &result);
			ft_memdel((void**)&line);
		}
		ft_putstr_fd("\n", 2);
	}
	return (result);
}