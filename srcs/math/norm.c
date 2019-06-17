#include "scop.h"
#include <math.h>

t_float3	norm3f(t_float3 v)
{
	float	len;

	len = sqrtf(dot3f(v, v));
	if (len > 0.0f)
		len = 1.0f / len;
	return (v * len);
}

t_float4	norm4f(t_float4 v)
{
	float	len;

	len = sqrtf(dot4f(v, v));
	if (len > 0.0f)
		len = 1.0f / len;
	return (v * len);
}