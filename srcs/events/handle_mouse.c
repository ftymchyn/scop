#include "scop.h"

int	handle_mouse(void *scop, SDL_Event *e)
{
	static t_bool	is_lbtn_pressed = FALSE;
	static t_int2	lmpos = (t_int2)(0);
	t_int2			mpos;
	t_scop			*s;
	t_float4		rquat;

	if (scop && e)
	{
		s = (t_scop*)scop;
		if (e->button.button == SDL_BUTTON_LEFT
		&& (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP))
		{
			is_lbtn_pressed = !is_lbtn_pressed;
			if (is_lbtn_pressed)
				lmpos = (t_int2){e->button.x, e->button.y};
		}
		else if (e->type == SDL_MOUSEMOTION && is_lbtn_pressed)
		{
			mpos = (t_int2){e->motion.x, e->motion.y};
			rquat = trackball_rotate(&s->scene.camera, lmpos, mpos);
			lmpos = mpos;
			s->scene.model.q_rotation = q_mult(s->scene.model.q_rotation, rquat);
		}
	}
	return (1);
}