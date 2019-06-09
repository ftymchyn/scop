#include "scop.h"

t_float3	cross3f(t_float3 v1, t_float3 v2)
{
	t_float3	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 3)
	{
		j = (i + 1) % 3;
		k = (i + 2) % 3;
		result[i] = (v1[j] * v2[k]) - (v1[k] * v2[j]);
		i++;
	}
	return (result);
}