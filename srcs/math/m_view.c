#include "scop.h"

t_mat4		m_view(t_camera *cam)
{
	t_mat4		result;

	m_identity(&result);
	result.d[11] = cam->pos.z * -1.0f;
	return (result);
}