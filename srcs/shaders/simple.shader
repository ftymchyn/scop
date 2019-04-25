//VERTEX SHADER
#version 330 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec3 a_color;

out vec4 frag_color;

void main()
{
	frag_color = vec4(a_color, 1.0);
	gl_Position = a_position;
}

//FRAGMENT SHADER
#version 330 core

in vec4 frag_color;

void main()
{
	gl_FragColor = frag_color;
}