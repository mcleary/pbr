#include "LinesMaterial.h"

LinesMaterial::LinesMaterial()
{
	program->attach(new Shader{ ShaderType::VERTEX, "shaders/lines_vert.glsl" });
	program->attach(new Shader{ ShaderType::FRAGMENT, "shaders/lines_frag.glsl" });
	program->link();
}

void LinesMaterial::bind()
{
	program->bind();
}