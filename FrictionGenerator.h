#pragma once

#include "ForceGenerator.h"

class FrictionGenerator : public ForceGenerator
{
public:
	FrictionGenerator(void);
	FrictionGenerator(const CL_Vec2f& normal, const CL_Vec2f& gravity, float friction);
	~FrictionGenerator(void);

	CL_Vec2f calculate(const Particle& particle) const;
private:
	CL_Vec2f acceleration;
};

