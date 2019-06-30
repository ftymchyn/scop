//VERTEX SHADER
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec3 frag_color;

uniform struct
{
	mat4 model;
	mat4 view;
	mat4 proj;
}		 u_mvp;

const vec3 directionToSun = vec3( -0.8, 0.8, 1.0 );

void main()
{
	vec3 l = normalize( directionToSun );
	vec3 n = normalize( transpose( inverse( mat3( u_mvp.model ) ) ) * a_normal );
	float intensity = max( 0.0, dot( n, l ) );
	frag_color = vec3( 0.7 ) * intensity;

	gl_Position = u_mvp.proj * u_mvp.view * u_mvp.model * vec4( a_position, 1.0 );
}

//FRAGMENT SHADER
#version 330 core

in vec3 frag_color;

void main()
{
	gl_FragColor = vec4(frag_color, 1.0);
}