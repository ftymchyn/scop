#include "scop.h"
#include <math.h>

t_float3	norm3f(t_float3 v)
{
	float	len;

	len = sqrtf(dot3f(v, v));
	len = 1.0f / len;
	return (v * len);
}