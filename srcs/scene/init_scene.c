#include "scop.h"

void	init_camera(t_camera *cam, float width, float height)
{
	cam->width = width;
	cam->height = height;
	cam->fov = 45.0f;
	cam->ar = cam->width / cam->height;
	cam->pos = (t_float3){ 0.0f, 0.0f, 3.0f };
}

void	init_scene(t_scene *scene)
{
	scene->model_shader = create_shader_program( "srcs/shaders/model.glsl");
	m_identity(&scene->m_model);
	m_identity(&scene->m_view);
	m_identity(&scene->m_proj);
}