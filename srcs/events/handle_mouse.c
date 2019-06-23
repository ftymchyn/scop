#include "scop.h"

static void	handle_mouse_wheel(t_scop *s, SDL_Event *e)
{
	s->scene.model.scale += e->wheel.y / (30.0f / s->scene.model.scale);
	s->scene.model.scale = MAX(0.005f, s->scene.model.scale);
}

static void	handle_mouse_motion(t_scop *s, SDL_Event *e)
{
	t_int2			motion_pos;
	t_float4		angle_axis;

	if (s->events.mleft_btn_pressed ^ s->events.mright_btn_pressed)
	{
		motion_pos = (t_int2){e->motion.x, e->motion.y};
		angle_axis = trackball_rotate(
			&s->scene.camera, s->events.last_motion_pos, motion_pos
		);
		s->events.last_motion_pos = motion_pos;
		if (s->events.mleft_btn_pressed)
		{
			angle_axis.xyz = q_rotate_vec3(
				s->scene.camera.q_rotation, angle_axis.xyz
			);
			s->scene.model.q_rotation = q_mult(
				s->scene.model.q_rotation, q_from_axis_angle(angle_axis)
			);
		}
		else
		{
			s->scene.camera.q_rotation = q_mult(
				s->scene.camera.q_rotation, q_from_axis_angle(angle_axis)
			);
		}
	}
}

static void	handle_mouse_btns(t_scop *s, SDL_Event *e)
{
	if (e->button.button == SDL_BUTTON_LEFT
		|| e->button.button == SDL_BUTTON_RIGHT)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			s->events.mleft_btn_pressed = !s->events.mleft_btn_pressed;
		}
		else
		{
			s->events.mright_btn_pressed = !s->events.mright_btn_pressed;
		}
		if (s->events.mright_btn_pressed ^ s->events.mleft_btn_pressed)
			s->events.last_motion_pos = (t_int2){e->button.x, e->button.y};
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
		else if (e->type == SDL_MOUSEMOTION)
			handle_mouse_motion(s, e);
		else if (e->type == SDL_MOUSEWHEEL)
			handle_mouse_wheel(s, e);
	}
	return (1);
}