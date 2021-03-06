#include "scop.h"

t_float4	q_from_axis_angle(t_float4 axis_angle)
{
	t_float4 result;

	result.xyz = norm3f(axis_angle.xyz) * sin(axis_angle.w * 0.5f);
	result.w = cos(axis_angle.w * 0.5f);
	return (result);
}

t_float4	q_mult(t_float4 q1, t_float4 q2)
{
	t_float4	result;
	t_float3	axis1;
	t_float3	axis2;

	axis1 = (t_float3){q1.x, q1.y, q1.z};
	axis2 = (t_float3){q2.x, q2.y, q2.z};
	result = (q1 * q2.w) + (q2 * q1.w);
	result.xyz += cross3f(axis2, axis1);
	result.w = q1.w * q2.w - dot3f(axis1, axis2);
	return (norm4f(result));
}

t_float3	q_rotate_vec3(t_float4 q, t_float3 v)
{
	t_float4	result;
	t_float4	q_conjugate;

	q_conjugate.xyz = q.xyz * -1.0f;
	q_conjugate.w = q.w;
	result = 
		q_mult(
			q_mult(
				q,
				(t_float4){v.x, v.y, v.z, 0.0f}
			),
			q_conjugate
		);
	return (result.xyz);
}