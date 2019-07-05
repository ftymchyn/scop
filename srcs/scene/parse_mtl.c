#include "scop.h"

static void	parse_color_statement(t_mtl *mtl, char *statement)
{
	t_float3	value;
	char		*type;
	t_darr		split_statement;

	split_statement = ft_strsplit_vec(statement, ' ');
	if (split_statement.size > 1)
	{
		value.xyz = ft_atof(*(char**)darr_at(&split_statement, 1));
		if (split_statement.size > 3)
		{
			value.y = ft_atof(*(char**)darr_at(&split_statement, 2));
			value.z = ft_atof(*(char**)darr_at(&split_statement, 3));
		}
		type = *(char**)darr_at(&split_statement, 0);
		if (ft_strequ(type, "Ka"))
			mtl->ka = value;
		else if (ft_strequ(type, "Kd"))
			mtl->kd = value;
		else if (ft_strequ(type, "Ks"))
			mtl->ks = value;
		else if (ft_strequ(type, "Ns"))
			mtl->ns = value.x;
	}
	darr_clear(&split_statement, (void (*)(void *))&ft_memdel);
}

static void	parse_texture_statement(t_mtl *mtl, char *statement, char *root)
{
	char	*type;
	char	*tex_path;
	t_darr	split_statement;

	split_statement = ft_strsplit_vec(statement, ' ');
	if (split_statement.size > 1)
	{
		tex_path = ft_strjoin(root, *(char**)darr_last(&split_statement));
		type = *(char**)darr_at(&split_statement, 0);
		if (ft_strequ(type, "map_Ka"))
			mtl->fmap_ka = tex_path;
		else if (ft_strequ(type, "map_Kd"))
			mtl->fmap_kd = tex_path;
		else if (ft_strequ(type, "map_Ks"))
			mtl->fmap_ks = tex_path;
		else if (ft_strequ(type, "map_Bump") || ft_strequ(type, "bump"))
			mtl->fmap_bump = tex_path;
		else
			ft_strdel(&tex_path);
	}
	darr_clear(&split_statement, (void (*)(void *))&ft_memdel);
}

static void	create_mtl(t_obj *obj, char *name)
{
	t_mtl	*mtl;

	mtl = (t_mtl*)darr_create_last(&obj->mtls);
	mtl->name = ft_strdup(name);
}

void	parse_mtl(t_obj *obj, char *root, char *filename)
{
	char	*path;
	char	*line;
	int		fd;

	path = ft_strjoin(root, filename);
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		ft_printf("  -Loading mtllib %s\n", path);
		root = ft_strsub(path, 0, ft_strrchr(path, '/') - path + 1);
		while (get_next_line(fd, &line) > 0)
		{
			if (ft_strnequ(line, "newmtl ", 7))
				create_mtl(obj, line + 7);
			else if (ft_strnequ(line, "Ka", 2) || ft_strnequ(line, "Kd", 2)
					|| ft_strnequ(line, "Ks", 2) || ft_strnequ(line, "Ns", 2))
				parse_color_statement((t_mtl*)darr_last(&obj->mtls), line);
			else if (ft_strnequ(line, "map", 3) || ft_strnequ(line, "bump", 4))
				parse_texture_statement(
					(t_mtl*)darr_last(&obj->mtls), line, root
				);
			ft_strdel(&line);
		}
		ft_strdel(&root);
	}
	ft_strdel(&path);
}