//VERTEX SHADER
#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 0) in vec2 a_texCoord;

out vec3 texDir;

uniform mat4 view;

void main()
{
	texDir = mat3(view) * vec3(a_texCoord, 1.0);
	gl_Position = vec4(a_position, 1.0, 1.0);
}

//FRAGMENT SHADER
#version 330 core

in vec3 texDir;

uniform samplerCube skyboxCubemap;

void main()
{
	gl_FragColor = texture(skyboxCubemap, texDir);
}