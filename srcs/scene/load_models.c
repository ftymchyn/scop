#include "scop.h"

static t_model	create_model_from_obj(t_obj obj)
{
	t_model		result;
	//t_mesh		mesh;

	ft_bzero(&result, sizeof(t_model));
	(void)(obj);
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
		while (obj.v.size > 0)
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