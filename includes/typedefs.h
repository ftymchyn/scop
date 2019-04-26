#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "scop.h"

typedef enum		s_bool
{
	FALSE = 0,
	TRUE
}					t_bool;

typedef struct		s_viewport
{
	unsigned int	width;
	unsigned int	height;
}					t_viewport;

typedef struct		s_scop
{
	t_bool			running;
	SDL_Window		*window;
	SDL_GLContext	*context;
	t_viewport		viewport;
}					t_scop;

#endif