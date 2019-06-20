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

static GLuint	create_cube(char *res_folder)
{
	GLuint		vao;
	char		*file;
	t_model		model;
	t_mesh		*mesh;

	vao = 0;
	file = ft_strjoin(res_folder, "cube.obj");
	model = load_model(file);
	if (model.meshes.size > 0)
	{
		mesh = (t_mesh*)darr_at(&model.meshes, 0);
		vao = mesh->vao;
		mesh->vao = 0;
		mesh->vbo_v = 0;
	}
	clear_model(&model);
	free(file);
	return (vao);
}

t_skybox	create_skybox(char *res_folder)
{
	t_skybox	skybox;

	ft_bzero(&skybox, sizeof(t_skybox));
	skybox.vao = create_cube(res_folder);
	skybox.cubemap = load_cubemap(res_folder);
	skybox.shader = create_shader_program( "srcs/shaders/skybox.glsl");
	return (skybox);
}