#include "scop.h"

void	m_identity(t_mat4 *mat4)
{
	if (mat4)
	{
		ft_bzero(mat4, sizeof(t_mat4));
		mat4->d[0] = 1.0f;
		mat4->d[5] = 1.0f;
		mat4->d[10] = 1.0f;
		mat4->d[15] = 1.0f;
	}
}