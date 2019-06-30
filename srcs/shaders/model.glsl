//VERTEX SHADER
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec4 frag_color;

uniform struct
{
	mat4 model;
	mat4 view;
	mat4 proj;
}		 u_mvp;

uniform struct
{
	vec3 dir;
	vec4 ka;
	vec4 kd;
}		 u_light;

void main()
{
	vec3 l = normalize( u_light.dir * -1.0 );
	vec3 n = normalize( transpose( inverse( mat3( u_mvp.model ) ) ) * a_normal );

	vec4 ambient = u_light.ka * u_light.kd;
	vec4 diffuse = u_light.kd * max( 0.0, dot( n, l ) );

	frag_color = ambient + diffuse;
	gl_Position = u_mvp.proj * u_mvp.view * u_mvp.model * vec4( a_position, 1.0 );
}

//FRAGMENT SHADER
#version 330 core

in vec4 frag_color;

void main()
{
	gl_FragColor = frag_color;
}