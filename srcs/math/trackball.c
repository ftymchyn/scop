#include "scop.h"

static t_float3	to_ball_rel(t_camera *cam, t_int2 pos)
{
	t_float3	result;

	result.x = pos.x - cam->width * 0.5f;
	result.y = pos.y - cam->height * 0.5f;
	if (cam->width > cam->height)
		result /= cam->height * 0.5f;
	else
		result /= cam->width * 0.5f;
	result *= -1.0f;
	result.z = 0.5f;
	return (result);
}

t_float4	trackball_rotate(t_camera *cam, t_int2 p1, t_int2 p2)
{
	t_float3	p[2];
	t_float3	vec;
	t_float3	axis;
	float		angle;
	float		dist;

	if (p1.x == p2.x && p1.y == p2.y)
		return ((t_float4){0.0f, 0.0f, 0.0f, 1.0f});
	p[0] = to_ball_rel(cam, p1);
	p[1] = to_ball_rel(cam, p2);
	vec = p[0] - p[1];
	dist = sqrtf(dot3f(vec, vec));
	dist = MIN(dist, 1.0f);
	dist = MAX(dist, -1.0f);
	axis = cross3f(p[1], p[0]);
	angle = 2.0f * asin(dist);
	return (q_angle_axis(axis, angle));
}