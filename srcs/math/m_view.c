#include "scop.h"

t_mat4		m_view(t_camera *cam)
{
	t_mat4		result;

	m_identity(&result);
	result.d[3] = cam->pos.x * -1.0f;
	result.d[7] = cam->pos.y * -1.0f;
	result.d[11] = (cam->pos.z + cam->near) * -1.0f;
	return (result);
}