#include "scop.h"

static void	update_skybox_shader(t_scene *scene)
{
	GLint	u_location;

	u_location = glGetUniformLocation(scene->skybox.shader, "view");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, scene->camera.m_view.d);
	u_location = glGetUniformLocation(scene->skybox.shader, "proj");
	glUniformMatrix4fv(u_location, 1, GL_TRUE, scene->camera.m_persp.d);
}

void	render_skybox(t_scop *s)
{
	GL_CALL(glUseProgram(s->scene.skybox.shader));
	update_skybox_shader(&s->scene);
	GL_CALL(glBindVertexArray(s->scene.skybox.vao));
	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, s->scene.skybox.cubemap));
	GL_CALL(glDepthFunc(GL_LEQUAL));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	GL_CALL(glDepthFunc(GL_LESS));
	GL_CALL(glBindVertexArray(0));
	GL_CALL(glUseProgram(0));
}