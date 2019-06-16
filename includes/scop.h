#ifndef SCOP_H
# define SCOP_H

# include <assert.h>
# include <SDL2/SDL.h>
# include <GL/glew.h>

# include "libft.h"
# include "typedefs.h"

# define ERROR_LOG_SIZE 1024
# define GL_CALL(gl_func) gl_skip_errors();gl_func;gl_check_errors(__FILE__, __LINE__)

void		create_context(t_scop *scop, int width, int height);
void		destroy_context(t_scop *scop);
void		gl_skip_errors();
void		gl_check_errors(char *file, int line);
GLuint		create_shader_program(const char *filename);

void		register_events(t_scop *scop);
int			handle_exit(void *scop, SDL_Event *e);
int			handle_keyboard(void *scop, SDL_Event *e);
int			handle_dropfile(void *scop, SDL_Event *e);
int			handle_mouse(void *scop, SDL_Event *e);

void		init_camera(t_camera *cam, float width, float height);
void		init_scene(t_scene *scene);
void		loop(t_scop *scop);

void		render_scene(t_scene *s);
void		render_model(t_darr *models);

t_darr		load_models(const char *filename, float *min_dist);
void		init_model(t_model *model);
void		clear_models(t_darr *models);
void		init_mesh(t_mesh *mesh);

void		init_obj(t_obj *obj);
void		parse_mtl(t_obj *obj, char *root, char *filename);
void		parse_obj_fd(int fd, t_obj *o, char *root);
void		clear_obj(t_obj *obj);

void		generate_buffers(t_mesh *mesh);
void		generate_normals(t_float3 **v, t_float3 **vn);

t_float3	cross3f(t_float3 v1, t_float3 v2);
t_float3	norm3f(t_float3 v);
float		dot3f(t_float3 v1, t_float3 v2);

void		m_identity(t_mat4 *mat4);
t_mat4		m_transpose(t_mat4 m);
t_mat4		m_view(t_camera *cam);
t_mat4		m_projection(t_camera *c);
t_mat4		m_mult(t_mat4 *m1, t_mat4 *m2);

#endif