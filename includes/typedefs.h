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

typedef	struct		s_mat4
{
	float			d[16];
}					t_mat4;

typedef struct		s_mtl
{
	t_float3		ka;
	t_float3		kd;
	t_float3		ks;
	float			ns;
	char			*fmap_kd;
	char			*fmap_ks;
	char			*fmap_bump;
}					t_mtl;

typedef struct		s_obj
{
	t_darr			v;
	t_darr			vn;
	t_darr			vt;
	t_darr			mtls;
	t_darr			objects;
	float			min_dist;
}					t_obj;

typedef struct		s_object
{
	t_obj			*data;
	t_darr			groups;
}					t_object;

typedef struct		s_group
{
	t_object		*owner;
	char			*name;
	t_darr			faces;
}					t_group;

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
	float			near;
	float			far;
	t_float2		rt_point;
	t_float3		pos;
}					t_camera;

typedef struct		s_scene
{
	t_camera		camera;
	t_darr			models;
	GLuint			model_shader;
	t_mat4			m_model;
	t_mat4			m_view;
	t_mat4			m_proj;
}					t_scene;

typedef struct		s_scop
{
	t_bool			running;
	SDL_Window		*window;
	SDL_GLContext	*context;
	t_scene			scene;
}					t_scop;

#endif