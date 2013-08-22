#include "GravityGenerator.h"


GravityGenerator::GravityGenerator() : ForceGenerator()
{
}


GravityGenerator::GravityGenerator(CL_Vec2f gravity) : ForceGenerator(), gravity(gravity)
{
}


GravityGenerator::~GravityGenerator(void)
{
}


CL_Vec2f GravityGenerator::calculate(const Particle& particle) const
{
	return gravity * particle.getMass();
}