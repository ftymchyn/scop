#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include "scop.h"

typedef int			t_int2 __attribute__((ext_vector_type(2)));
typedef int			t_int3 __attribute__((ext_vector_type(3)));
typedef GLfloat		t_float2 __attribute__((ext_vector_type(2)));
typedef GLfloat		t_float3 __attribute__((ext_vector_type(3)));
typedef GLfloat		t_float4 __attribute__((ext_vector_type(4)));

typedef enum		s_bool
{
	FALSE = 0,
	TRUE
}					t_bool;

typedef	struct		s_mat4
{
	float			d[16];
}					t_mat4;

typedef	struct		s_tex
{
	unsigned char	*data;
	int				width;
	int				height;
	int				channels;
}					t_tex;

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
	t_float3		min_p;
	t_float3		max_p;
	t_float3		mid_vec;
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
	const char		*id;
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
	t_float4		q_rotation;
	t_float4		translation;
	float			scale;
}					t_model;

typedef struct		s_camera
{
	unsigned int	w;
	unsigned int	h;
	t_float3		pos;
	t_float4		q_rotation;
	t_mat4			m_view;
	t_mat4			m_persp;
	t_mat4			m_ortho;
}					t_camera;

typedef struct		s_skybox
{
	GLuint			vao;
	GLuint			cubemap;
	GLuint			shader;
}					t_skybox;

typedef struct		s_scene
{
	t_camera		camera;
	t_skybox		skybox;
	t_model			model;
	GLuint			model_shader;
}					t_scene;

typedef struct		s_events
{
	t_bool			should_close;
	t_bool			mleft_btn_pressed;
	t_bool			mright_btn_pressed;
	t_int2			last_motion_pos;
	t_bool			is_ortho_projection;
}					t_events;

typedef struct		s_scop
{
	SDL_Window		*window;
	SDL_GLContext	*context;
	t_events		events;
	t_scene			scene;
}					t_scop;

#endif