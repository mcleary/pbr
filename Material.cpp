#include "Material.h"

Material::Material()
{
	program = std::make_shared<Program>();
}

template<typename MapType>
void Material::bindParams(const MapType& paramsMap)
{
	for (const auto& p : paramsMap)
	{
		program->setUniform(p.first, p.second);
	}
}

void Material::bindParams(const MaterialParams& params)
{
	bindParams(params.floatValues);
	bindParams(params.vec3Values);
	bindParams(params.mat4Values);
}