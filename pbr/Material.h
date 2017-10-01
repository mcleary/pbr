#pragma once

#include "Shader.h"
#include "MaterialParams.h"

class Material
{
public:
	explicit Material();

	virtual void bind() = 0;
	virtual void unbind() = 0;	

	void bindParams(const MaterialParams& params);

	std::shared_ptr<Program> program;

private:
	template<typename MapType>
	void bindParams(const MapType& paramsMap);
};