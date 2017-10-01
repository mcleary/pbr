#pragma once

#include <glm/glm.hpp>

#include <map>
#include <string>

class MaterialParams
{
public:
	void set(const std::string& name, float value) 
	{ 
		floatValues[name] = value;
	}

	void set(const std::string& name, const glm::vec3& value) 
	{ 
		vec3Values[name] = value;
	}

	void set(const std::string& name, const glm::mat4 value) 
	{ 
		mat4Values[name] = value;
	}

	std::map<std::string, float>	 floatValues;
	std::map<std::string, glm::vec3> vec3Values;
	std::map<std::string, glm::mat4> mat4Values;
};