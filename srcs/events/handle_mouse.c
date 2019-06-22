#include "scop.h"

static void	handle_mouse_motion(t_scop *s, SDL_Event *e)
{
	t_int2			mouse_pos;
	t_float4		rquat;

	if (e->type == SDL_MOUSEMOTION && s->events.mleft_btn_pressed)
	{
		mouse_pos = (t_int2){e->motion.x, e->motion.y};
		rquat = trackball_rotate(
			&s->scene.camera, s->events.last_mouse_pos, mouse_pos
		);
		s->events.last_mouse_pos = mouse_pos;
		s->scene.model.q_rotation = q_mult(s->scene.model.q_rotation, rquat);
	}
}

static void	handle_mouse_btns(t_scop *s, SDL_Event *e)
{
	if (e->button.button == SDL_BUTTON_LEFT)
	{
		s->events.mleft_btn_pressed = !s->events.mleft_btn_pressed;
		if (s->events.mleft_btn_pressed)
			s->events.last_mouse_pos = (t_int2){e->button.x, e->button.y};
	}
}

int			handle_mouse(void *scop, SDL_Event *e)
{
	t_scop	*s;

	if (scop && e)
	{
		s = (t_scop*)scop;
		if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
			handle_mouse_btns(s, e);
		if (e->type == SDL_MOUSEMOTION)
			handle_mouse_motion(s, e);
	}
	return (1);
}