#include "scop.h"

void	generate_buffers(t_mesh *mesh)
{
	GL_CALL(glGenVertexArrays(1, &mesh->vao));
	GL_CALL(glBindVertexArray(mesh->vao));
	GL_CALL(glGenBuffers(1, &mesh->vbo_v));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_v));
	GL_CALL(glBufferData(
		GL_ARRAY_BUFFER, (mesh->v.size * mesh->v.data_type_size),
		mesh->v.data, GL_STATIC_DRAW));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, sizeof(t_float3), 0));
	GL_CALL(glGenBuffers(1, &mesh->vbo_vn));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_vn));
	GL_CALL(glBufferData(
		GL_ARRAY_BUFFER, (mesh->vn.size * mesh->vn.data_type_size),
		mesh->vn.data, GL_STATIC_DRAW));
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(
		1, 3, GL_FLOAT, GL_FALSE, sizeof(t_float3), 0));
	GL_CALL(glGenBuffers(1, &mesh->vbo_vt));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo_vt));
	GL_CALL(glBufferData(
		GL_ARRAY_BUFFER, (mesh->vt.size * mesh->vt.data_type_size),
		mesh->vt.data, GL_STATIC_DRAW));
	GL_CALL(glEnableVertexAttribArray(2));
	GL_CALL(glVertexAttribPointer(
		2, 2, GL_FLOAT, GL_FALSE, sizeof(t_float2), 0));
	GL_CALL(glBindVertexArray(0));
}

void	generate_normals(t_float3 **v, t_float3 **vn)
{
	t_float3 normal;

	normal = cross3f((*v[1] - *v[0]), (*v[2] - *v[0]));
	normal = norm3f(normal);
	vn[0]->xyz = normal;
	vn[1]->xyz = normal;
	vn[2]->xyz = normal;
}