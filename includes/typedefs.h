#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "scop.h"

typedef int			t_int3 __attribute__((ext_vector_type(3)));
typedef GLfloat		t_float3 __attribute__((ext_vector_type(3)));

typedef enum		s_bool
{
	FALSE = 0,
	TRUE
}					t_bool;

typedef struct		s_obj
{
	t_darr			v;
	t_darr			vn;
	t_darr			vt;
	t_darr			f;
}					t_obj;

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