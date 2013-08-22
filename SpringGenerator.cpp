#include "SpringGenerator.h"


SpringGenerator::SpringGenerator(void)
{
}


SpringGenerator::SpringGenerator(const CL_Vec2f& position, float length, float coefficient)
	: position(position), length(length), coefficient(coefficient)
{
}


SpringGenerator::~SpringGenerator(void)
{
}


CL_Vec2f SpringGenerator::calculate(const Particle& particle) const
{
	CL_Vec2f d = position - particle.getPosition();

	return CL_Vec2f::normalize(d) * (d.length() - length) * coefficient;
}