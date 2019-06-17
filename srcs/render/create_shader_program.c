#include "scop.h"

static int	print_compile_error(GLuint shader_id, GLenum shader_type)
{
	GLint	compile_status;
	GLchar	buffer[ERROR_LOG_SIZE];
	int		len;

	len = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE)
	{
		glGetShaderInfoLog(shader_id, ERROR_LOG_SIZE, &len, buffer);
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
	GLchar	buffer[ERROR_LOG_SIZE];
	int		len;

	len = 0;
	glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
	if (link_status != GL_TRUE)
	{
		glGetProgramInfoLog(program_id, ERROR_LOG_SIZE, &len, buffer);
		ft_putendl_fd("Shader program LINK ERROR :", 2);
		ft_putendl_fd(buffer, 2);
		len++;
	}
	return (len);
}

static GLuint	create_shader(GLenum type, const char *src)
{
	GLuint	result;
	char	*src_end;
	int		len;

	result = 0;
	if (src)
	{
		src_end = ft_strstr(ft_strstr(src, "void main()"), "#version");
		len = src_end - src;
		result = glCreateShader(type);
		glShaderSource(result, 1, (const GLchar**)&src, (src_end ? &len : NULL));
		glCompileShader(result);
		if (print_compile_error(result, type))
		{
			glDeleteShader(result);
			result = 0;
		}
	}
	return (result);
}

GLuint	create_shader_program(const char *filename)
{
	GLuint	result;
	char	*source;
	GLuint	vert;
	GLuint	frag;

	result = 0;
	source = read_file(filename);
	vert = create_shader(GL_VERTEX_SHADER, ft_strstr(source, "//VERTEX"));
	frag = create_shader(GL_FRAGMENT_SHADER, ft_strstr(source, "//FRAGMENT"));
	if (vert && frag)
	{
		result = glCreateProgram();
		glAttachShader(result, vert);
		glAttachShader(result, frag);
		glLinkProgram(result);
		if (print_link_error(result))
		{
			glDeleteProgram(result);
			result = 0;
		}
		glDeleteShader(vert);
		glDeleteShader(frag);
	}
	free(source);
	return (result);
}