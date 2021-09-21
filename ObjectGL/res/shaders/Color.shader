#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 v_Color;
uniform mat4 u_MVP;
out vec4 color;

void main()
{
	gl_Position = u_MVP * position;
	color = v_Color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 u_Color;
in vec4 color;

void main()
{
	u_Color = color;
}
