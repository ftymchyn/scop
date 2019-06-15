#include "scop.h"

void	init_camera(t_camera *cam, float width, float height)
{
	float	fov_y;
	float	aspect;

	fov_y = 45.0f;
	aspect = width / height;
	cam->width = width;
	cam->height = height;
	cam->pos = (t_float3){ 0.0f, 0.0f, 3.0f };
	cam->near = 1.0f;
	cam->far = 100.0f;
	cam->rt_point.y = tanf(fov_y * 0.5 * 3.14159f / 180.0f) * cam->near;
	cam->rt_point.x = cam->rt_point.y * aspect;
}

void	init_scene(t_scene *scene)
{
	scene->model_shader = create_shader_program( "srcs/shaders/model.glsl");
	m_identity(&scene->m_model);
	m_identity(&scene->m_view);
	m_identity(&scene->m_proj);
}