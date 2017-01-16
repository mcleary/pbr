#pragma once

#include "Material.h"

class LinesMaterial : public Material
{
public:
	explicit LinesMaterial();

	virtual void bind() override;
	virtual void unbind() override {}
};