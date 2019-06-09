#ifndef SCOP_H
# define SCOP_H

# include <assert.h>
# include <SDL2/SDL.h>
# include <GL/glew.h>

# include "libft.h"
# include "typedefs.h"

# define ERROR_LOG_SIZE 1024
# define GL_CALL(gl_func) gl_skip_errors();gl_func;gl_check_errors(__FILE__, __LINE__)

void	create_context(t_scop *scop, int width, int height);
void	destroy_context(t_scop *scop);
void	gl_skip_errors();
void	gl_check_errors(char *file, int line);
GLuint	create_shader_program(const char *filename);

void	register_events(t_scop *scop);
int		handle_exit(void *scop, SDL_Event *e);
int		handle_keyboard(void *scop, SDL_Event *e);
int		handle_dropfile(void *scop, SDL_Event *e);

void	loop(t_scop *scop);

t_darr	load_models(const char *filename);
void	init_model(t_model *model);
void	clear_models(t_darr *models);
void	init_mesh(t_mesh *mesh);
void	init_obj(t_obj *obj);
t_obj	parse_obj(int fd);
void	clear_obj(t_obj *obj);

void	generate_buffers(t_mesh *mesh);

#endif