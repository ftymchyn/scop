#ifndef SCOP_H
# define SCOP_H

# include <assert.h>
# include <SDL2/SDL.h>
# include <GL/glew.h>

# include "libft.h"
# include "typedefs.h"

# define ERROR_LOG_SIZE 1024

void			create_context(t_scop *scop, int width, int height);
void			destroy_context(t_scop *scop);
GLuint			create_shader_program(const char *filename);

void			register_events(t_scop *scop);
int				handle_exit(void *scop, SDL_Event *e);
int				handle_keyboard(void *scop, SDL_Event *e);
int				handle_dropfile(void *scop, SDL_Event *e);

void			loop(t_scop *scop);

t_obj			parse_obj(const char *filename);

#endif