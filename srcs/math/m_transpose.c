#include "scop.h"

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