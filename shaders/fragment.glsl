#version 330 core

in vec3 v_normal;
in vec2 v_uv;

out vec4 color;

void main()
{
    color = vec4(normalize(v_normal.xyz), 0.5);
}
