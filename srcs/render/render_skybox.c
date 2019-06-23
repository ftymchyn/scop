#include "scop.h"

static void	update_skybox_shader(t_scene *s)
{
	GLint	u_location;

	u_location = glGetUniformLocation(s->skybox.shader, "view");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->camera.m_view.d);
	u_location = glGetUniformLocation(s->skybox.shader, "proj");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, s->camera.m_proj.d);
}

void	render_skybox(t_scene *scene)
{
	GL_CALL(glUseProgram(scene->skybox.shader));
	update_skybox_shader(scene);
	GL_CALL(glBindVertexArray(scene->skybox.vao));
	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, scene->skybox.cubemap));
	GL_CALL(glDepthFunc(GL_LEQUAL));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	GL_CALL(glDepthFunc(GL_LESS));
	GL_CALL(glBindVertexArray(0));
	GL_CALL(glUseProgram(0));
}