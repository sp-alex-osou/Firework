#include "ThrustGenerator.h"

#include <random>


ThrustGenerator::ThrustGenerator() : ForceGenerator()
{
}


ThrustGenerator::ThrustGenerator(float thrust, CL_Vec2f direction) : ForceGenerator(), thrust(thrust), direction(direction)
{
}


ThrustGenerator::~ThrustGenerator()
{
}


CL_Vec2f ThrustGenerator::calculate(const Particle& particle) const
{
	CL_Vec2f tmpDirection = direction;

	if (direction == CL_Vec2f(0, 0))
		tmpDirection = CL_Vec2f(rand(), rand());
		
	return CL_Vec2f::normalize(tmpDirection) * thrust;
}


float ThrustGenerator::rand() const
{
	return 2 * (std::rand() / (float)RAND_MAX) - 1;
}