#include "scop.h"

static void		clear_face(void *data)
{
	t_darr	*darr;

	darr = (t_darr*)data;
	darr_clear(darr, NULL);
}

void	clear_obj(t_obj *obj)
{
	if (obj)
	{
		darr_clear( &obj->v, NULL );
		darr_clear( &obj->vn, NULL );
		darr_clear( &obj->vt, NULL );
		darr_clear( &obj->f, &clear_face );
	}
}