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

typedef struct		s_facegr
{
	//t_mtl			*mtl;
	t_darr			faces;
}					t_facegr;

typedef struct		s_obj
{
	t_darr			v;
	t_darr			vn;
	t_darr			vt;
	t_darr			*buffers[3];
	t_darr			fgroups;
	t_facegr		gr;
	size_t			faces_num;
}					t_obj;

typedef struct		s_material
{
	t_float3		ka;
	t_float3		kd;
	t_float3		ks;
	float			ns;
}					t_material;

typedef struct		s_mesh
{
	t_darr			v;
	t_darr			vn;
	t_darr			vt;
	GLuint			vao;
	GLuint			vbo_v;
	GLuint			vbo_vt;
	GLuint			vbo_vn;
}					t_mesh;

typedef struct		s_model
{
	t_darr			materials;
	t_darr			meshes;
}					t_model;

typedef struct		s_camera
{
	unsigned int	width;
	unsigned int	height;
}					t_camera;

typedef struct		s_scene
{
	t_camera		camera;
	t_darr			models;
}					t_scene;

typedef struct		s_scop
{
	t_bool			running;
	SDL_Window		*window;
	SDL_GLContext	*context;
	t_scene			scene;
}					t_scop;

#endif