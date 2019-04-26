#ifndef SCOP_H
# define SCOP_H

# include <assert.h>
# include <SDL2/SDL.h>
# include <GL/glew.h>

# include "libft.h"
# include "typedefs.h"

void			create_context(t_scop *scop, int width, int height);
void			destroy_context(t_scop *scop);
GLuint			create_shader_program(const char *filename);

void			loop(t_scop *scop);

#endif