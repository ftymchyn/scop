#include "scop.h"

void	create_context(t_scop *scop, int width, int height)
{
	int ret;

	ft_bzero(scop, sizeof(t_scop));
	ret = SDL_Init(SDL_INIT_VIDEO);
	assert(ret == 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	scop->window = SDL_CreateWindow(
		"scop",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	assert(scop->window);
	scop->context = SDL_GL_CreateContext(scop->window);
	assert(scop->context);
	ret = glewInit();
	assert(ret == GLEW_OK);
	scop->viewport.width = width;
	scop->viewport.height = height;
}

void	destroy_context(t_scop *scop)
{
	SDL_GL_DeleteContext(scop->context);
	SDL_DestroyWindow(scop->window);
	SDL_Quit();
}