#include "scop.h"

static t_float2	compute_right_top_point(float w, float h, float near)
{
	t_float2	result;
	const float	fov_y = 70.0f;
	const float	aspect = w / h;

	result.y = tanf(fov_y * 0.5 * 3.14159f / 180.0f) * near;
	result.x = result.y * aspect;
	return (result);
}

t_mat4			m_persp(float w, float h, float near, float far)
{
	t_mat4		result;
	t_float2	rt_point;

	m_identity(&result);
	rt_point = compute_right_top_point(w, h, near);
	result.d[0] = near / rt_point.x;
	result.d[5] = near / rt_point.y;
	result.d[10] = -(far + near) / (far - near);
	result.d[11] = -2.0f * far * near / (far - near);
	result.d[14] = -1.0f;
	result.d[15] = 0.0f;
	return (result);
}

t_mat4			m_ortho(float w, float h, float near, float far)
{
	t_mat4		result;
	t_float2	rt_point;

	m_identity(&result);
	rt_point = compute_right_top_point(w, h, near);
	result.d[0] = 1.0f / rt_point.x;
	result.d[5] = 1.0f / rt_point.y;
	result.d[10] = -2.0f / (far - near);
	result.d[11] = (far + near) / (far - near) * -1.0f;
	return (result);
}