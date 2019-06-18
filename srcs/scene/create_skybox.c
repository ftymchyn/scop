#include "scop.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void		setup_cubemap_parameters()
{
	GL_CALL(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
	);
	GL_CALL(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
	);
	GL_CALL(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
	);
	GL_CALL(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
	);
	GL_CALL(
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE)
	);
}

static GLuint	load_cubemap(char *folder)
{
	GLuint	cubemap;
	char	*faces[] = {"right.jpg", "left.jpg", "top.jpg",
						"bottom.jpg", "front.jpg", "back.jpg"};
	char	*file;
	t_tex	tex;
	int		i;

	GL_CALL(glGenTextures(1, &cubemap));
	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap));
	i = -1;
	while (++i < 6)
	{
		file = ft_strjoin(folder, faces[i]);
		tex.data = stbi_load(file, &tex.width, &tex.height, &tex.channels, 0);
		ft_memdel((void**)&file);
		GL_CALL(
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
				tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.data)
		);
		stbi_image_free(tex.data);
	}
	setup_cubemap_parameters();
	return (cubemap);
}

static GLuint	create_quad()
{
	GLuint		vao;
	GLuint		vbo[2];
	int			i;
	const float	buffer[] = {
		-1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f
	};

	GL_CALL(glGenVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));
	GL_CALL(glGenBuffers(2, vbo));
	i = -1;
	while (++i < 2)
	{
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo[i]));
		GL_CALL(
			glBufferData(
				GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW)
		);
		GL_CALL(glEnableVertexAttribArray(i));
		GL_CALL(
			glVertexAttribPointer(
				i, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid *)0)
		);
	}
	return (vao);
}

t_skybox	create_skybox(char *res_folder)
{
	t_skybox	skybox;

	ft_bzero(&skybox, sizeof(t_skybox));
	skybox.vao = create_quad();
	skybox.cubemap = load_cubemap(res_folder);
	skybox.shader = create_shader_program( "srcs/shaders/skybox.glsl");
	return (skybox);
}