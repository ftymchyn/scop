#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "scop.h"

typedef int			t_int3 __attribute__((ext_vector_type(3)));
typedef GLfloat		t_float2 __attribute__((ext_vector_type(2)));
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

typedef struct		s_camera
{
	unsigned int	width;
	unsigned int	height;
}					t_camera;

typedef struct		s_scene
{
	t_camera		camera;
}					t_scene;

typedef struct		s_scop
{
	t_bool			running;
	SDL_Window		*window;
	SDL_GLContext	*context;
	t_scene			scene;
}					t_scop;

#endif