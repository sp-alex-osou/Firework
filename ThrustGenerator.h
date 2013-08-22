#pragma once

#include "ForceGenerator.h"

class ThrustGenerator : public ForceGenerator
{
public:
	ThrustGenerator();
	ThrustGenerator(float thrust, CL_Vec2f direction = CL_Vec2f(0, 0));
	~ThrustGenerator(void);

	CL_Vec2f calculate(const Particle& particle) const;
private:
	float rand() const;

	float thrust;
	CL_Vec2f direction;
};