//VERTEX SHADER
#version 330 core

layout(location = 0) in vec3 a_position;

out vec3 texDir;

uniform mat4 view;
uniform mat4 proj;

void main()
{
	texDir = a_position;
	texDir.z *= -1.0;
	gl_Position = proj * view * vec4(a_position, 1.0);
	gl_Position = gl_Position.xyww;
}

//FRAGMENT SHADER
#version 330 core

in vec3 texDir;

uniform samplerCube skyboxCubemap;

void main()
{
	gl_FragColor = texture(skyboxCubemap, texDir);
}