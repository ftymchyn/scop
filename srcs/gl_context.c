#include "scop.h"

static void	gl_attrib_setup()
{
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void	create_context(t_scop *scop, int width, int height)
{
	int ret;

	ft_bzero(scop, sizeof(t_scop));
	ret = SDL_Init(SDL_INIT_VIDEO);
	assert(ret == 0);
	gl_attrib_setup();
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
	init_camera(&scop->scene.camera, width, height);
	init_scene(&scop->scene);
}

void	destroy_context(t_scop *scop)
{
	SDL_GL_DeleteContext(scop->context);
	SDL_DestroyWindow(scop->window);
	SDL_Quit();
}

void	gl_skip_errors()
{
	while(glGetError());
}

void	gl_check_errors(char *file, int line)
{
	GLenum error;

	error = GL_NO_ERROR;
	while((error = glGetError()))
	{
		ft_dprintf(2, "GL ERROR %x\nline: %d\nfile: %s\n", error, line, file);
	}
}