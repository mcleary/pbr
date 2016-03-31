#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 ModelView;
uniform mat4 Projection;

out vec3 v_normal;
out vec2 v_uv;

void main()
{
    v_normal = normal;
    v_uv = uv;

	gl_Position = Projection * ModelView * vec4(position, 1.0);
}
