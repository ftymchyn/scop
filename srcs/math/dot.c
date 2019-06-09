#include "scop.h"

float	dot3f(t_float3 v1, t_float3 v2)
{
	float	result;
	int			i;

	i = 0;
	result = 0.0f;
	while (i < 3)
	{
		result += v1[i] * v2[i];
		i++;
	}
	return (result);
}