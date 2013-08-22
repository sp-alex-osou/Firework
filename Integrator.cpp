#include "Integrator.h"


Integrator::Integrator(void)
{
}


Integrator::~Integrator(void)
{
}


void Integrator::integrate(Particle& particle, const CL_Vec2f& force, float time) const
{
	particle.velocity += (force / particle.mass) * time;
	particle.position += particle.velocity * time;
}