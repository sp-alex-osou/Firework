#pragma once

#include "Include.h"
#include "Particle.h"

class ForceGenerator
{
public:
	virtual ~ForceGenerator() {}

	virtual CL_Vec2f calculate(const Particle& particle) const = 0;
};