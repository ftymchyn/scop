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

t_mat4	m_transpose(t_mat4 m)
{
	t_mat4	result;
	size_t	i;

	i = 0;
	while (i < 4)
	{
		result.d[i] = m.d[i * 4];
		result.d[i + 4] = m.d[i * 4 + 1];
		result.d[i + 8] = m.d[i * 4 + 2];
		result.d[i + 12] = m.d[i * 4 + 3];
		i++;
	}
	return (result);
}

t_mat4	m_mult(t_mat4 *m1, t_mat4 *m2)
{
	t_mat4	result;
	size_t	i;
	size_t	k;

	i = -1;
	while (++i < 4)
	{
		k = -1;
		while (++k < 4)
		{
			result.d[i * 4 + k] =
			m1->d[i * 4] * m2->d[i * 4 + k]
			+ m1->d[i * 4 + 1] * m2->d[i * 4 + k]
			+ m1->d[i * 4 + 2] * m2->d[i * 4 + k]
			+ m1->d[i * 4 + 3] * m2->d[i * 4 + k];
		}
	}
	return (result);
}

t_mat4	m_rotmatrix_quat(t_float4 q)
{
	t_mat4	m;

	m_identity(&m);
	m.d[0] = 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
	m.d[1] = 2.0 * (q[0] * q[1] - q[2] * q[3]);
	m.d[2] = 2.0 * (q[2] * q[0] + q[1] * q[3]);
	m.d[4] = 2.0 * (q[0] * q[1] + q[2] * q[3]);
	m.d[5] = 1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]);
	m.d[6] = 2.0 * (q[1] * q[2] - q[0] * q[3]);
	m.d[8] = 2.0 * (q[2] * q[0] - q[1] * q[3]);
	m.d[9] = 2.0 * (q[1] * q[2] + q[0] * q[3]);
	m.d[10] = 1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]);
	return (m);
}

t_mat4	m_scale(float scale)
{
	t_mat4	m;

	m_identity(&m);
	m.d[0] = scale;
	m.d[5] = scale;
	m.d[10] = scale;
	return (m);
}