#include "scop.h"

t_mat4		m_lookat(t_float3 pos, t_camera *cam)
{
	t_mat4		result;

	(void)pos;
	m_identity(&result);
	result.d[11] = cam->pos.z * -1.0f;
	return (result);
}