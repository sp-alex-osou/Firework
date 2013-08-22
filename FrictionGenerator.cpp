#include "FrictionGenerator.h"


FrictionGenerator::FrictionGenerator(void)
{
}


FrictionGenerator::FrictionGenerator(const CL_Vec2f& normal, const CL_Vec2f& gravity, float frictionCoefficient)
{
	CL_Vec2f direction = CL_Vec2f::rotate(normal, CL_Vec2f(0, 0), CL_Angle::from_degrees(90));

	if (direction.y > 0)
		direction *= -1;

	CL_Vec2f driving = direction * CL_Vec2f::dot(direction, gravity);
	CL_Vec2f friction = -direction * CL_Vec2f::dot(-normal, gravity) * frictionCoefficient;
	
	acceleration = (driving.length() > friction.length()) ? driving + friction : CL_Vec2f(0, 0);
}


FrictionGenerator::~FrictionGenerator(void)
{
}


CL_Vec2f FrictionGenerator::calculate(const Particle& particle) const
{
	return acceleration * particle.getMass();
}