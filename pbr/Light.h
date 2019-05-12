#pragma once

#include "Transform.h"

class Light 
{
public:	
	explicit Light(glm::vec3 Position);

	Transform transform;
};