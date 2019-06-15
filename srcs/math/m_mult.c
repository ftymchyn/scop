#include "scop.h"

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
			+ m1->d[i * 4 + 1] * m2->d[i * 4 + k + 4]
			+ m1->d[i * 4 + 2] * m2->d[i * 4 + k + 8]
			+ m1->d[i * 4 + 3] * m2->d[i * 4 + k + 12];
		}
	}
	return (result);
}