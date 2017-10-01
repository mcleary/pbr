#pragma once

#include "Transform.h"

class Light 
{
public:	
	explicit Light(glm::vec3 position);

	Transform transform;
};