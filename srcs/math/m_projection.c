#include "scop.h"

t_mat4	m_projection(t_camera *c)
{
	t_mat4	result;

	m_identity(&result);
	result.d[0] = c->near / c->rt_point.x;
	result.d[5] = c->near / c->rt_point.y;
	result.d[10] = -(c->far + c->near) / (c->far - c->near);
	result.d[11] = -2.0f * c->far * c->near / (c->far - c->near);
	result.d[14] = -1.0f;
	result.d[15] = 0.0f;
	return (result);
}