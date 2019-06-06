#include "scop.h"

static void		clear_face(void *data)
{
	t_darr	*darr;

	darr = (t_darr*)data;
	darr_clear(darr, NULL);
}

static void		clear_faces_groups(void *data)
{
	t_facegr	*facegr;

	facegr = (t_facegr*)data;
	darr_clear(&facegr->faces, &clear_face);
}

void	clear_obj(t_obj *obj)
{
	if (obj)
	{
		darr_clear( &obj->v, NULL );
		darr_clear( &obj->vn, NULL );
		darr_clear( &obj->vt, NULL );
		darr_clear( &obj->fgroups, &clear_faces_groups );
	}
}