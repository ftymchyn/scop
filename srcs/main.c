#include "scop.h"

int	main(void)
{
	int running = 1;
	SDL_Window *window = SDL_CreateWindow(
		"scop",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	assert(window);
	SDL_GLContext *glcontext = SDL_GL_CreateContext(window);
	assert(glcontext);
	GLenum result = glewInit();
	assert(result == GLEW_OK);
	
	GLfloat buffer[] = {
		-0.5f, -0.5f,  1.0f, 0.1f, 0.1f,
		 0.5f, -0.5f,  0.1f, 1.0f, 0.1f,
		 0.5f,  0.5f,  1.0f, 0.1f, 0.1f,
		-0.5f,  0.5f,  0.1f, 0.1f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 2));

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint program = create_shader_program( "srcs/shaders/simple.shader");

	while (running)
	{
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT
				|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				running = 0;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glUseProgram(program);
		
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);
		glUseProgram(0);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	return (0);
}