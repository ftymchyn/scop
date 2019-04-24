#include "scop.h"

static int	print_compile_error(GLuint shader_id, GLenum shader_type)
{
	GLint	compile_status;
	GLchar	buffer[1024];
	int		len;

	len = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE)
	{
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		glGetShaderInfoLog(shader_id, len, &len, buffer);
		ft_putstr_fd((shader_type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), 2);
		ft_putendl_fd(" shader COMPILE ERROR :", 2);
		ft_putendl_fd(buffer, 2);
		len++;
	}
	return (len);
}

static int	print_link_error(GLuint program_id)
{
	GLint	link_status;
	GLchar	buffer[1024];
	int		len;

	len = 0;
	glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		glGetProgramInfoLog(program_id, len, &len, buffer);
		ft_putendl_fd("Shader program LINK ERROR :", 2);
		ft_putendl_fd(buffer, 2);
		len++;
	}
	return (len);
}

static GLuint	create_shader(GLenum type, const char *filename)
{
	GLuint	result;
	GLchar	*source;

	result = 0;
	source = (GLchar*)read_file(filename);
	if (source)
	{
		result = glCreateShader(type);
		glShaderSource(result, 1, (const GLchar**)&source, NULL);
		glCompileShader(result);
		if (print_compile_error(result, type))
		{
			glDeleteShader(result);
			result = 0;
		}
		free(source);
	}
	return (result);
}

GLuint	create_shader_program(const char *vsfile, const char *fsfile)
{
	GLuint	result;
	GLuint	vertex;
	GLuint	fragment;

	result = 0;
	vertex = create_shader(GL_VERTEX_SHADER, vsfile);
	fragment = create_shader(GL_FRAGMENT_SHADER, fsfile);
	if (vertex && fragment)
	{
		result = glCreateProgram();
		glAttachShader(result, vertex);
		glAttachShader(result, fragment);
		glLinkProgram(result);
		if (print_link_error(result))
		{
			glDeleteProgram(result);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			result = 0;
		}
	}
	return (result);
}