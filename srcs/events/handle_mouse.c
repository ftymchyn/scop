#include "scop.h"

int	handle_mouse(void *scop, SDL_Event *e)
{
	static t_bool	is_lbtn_pressed = FALSE;

	if (scop && e)
	{
		if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
		{
			if (e->button.button == SDL_BUTTON_LEFT)
				is_lbtn_pressed = !is_lbtn_pressed;
		}
		else if (e->type == SDL_MOUSEMOTION && is_lbtn_pressed)
		{
			ft_printf("x %d, y %d\n", e->motion.x, e->motion.y);
		}
	}
	return (1);
}