//VERTEX SHADER
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec3 frag_color;

void main()
{
	float intensity = dot(a_normal, vec3(0.0, 0.0, 1.0));
	if (intensity < 0.0)
		intensity = 0.0;
	frag_color = vec3(1.0) * intensity;
	gl_Position = vec4(a_position, 1.0);
}

//FRAGMENT SHADER
#version 330 core

in vec3 frag_color;

void main()
{
	gl_FragColor = vec4(frag_color, 1.0);
}