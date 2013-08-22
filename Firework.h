#pragma once

#include "GameComponent.h"
#include "Particle.h"
#include "ParticleRegistry.h"
#include "Integrator.h"
#include "GravityGenerator.h"
#include "ThrustGenerator.h"
#include "DragGenerator.h"
#include "SpringGenerator.h"
#include "SpringPairGenerator.h"
#include "Line.h"

#include <list>

class Firework : public GameComponent
{
public:
	Firework(Game& game);
	~Firework(void);

	void init();
	void update(float elapsed);
	void draw(float elapsed);
private:
	CL_Vec2f scale(const CL_Vec2f& v) const;
	std::pair<CL_Vec2f, const Line*> checkCollision(const CL_Vec2f& prevPosition, Particle& particle, const std::list<Line>& lines, bool& collision) const;
	CL_Vec2f getIntersection(const Line& line1, const Line& line2) const;
	CL_Vec2f reflect(const CL_Vec2f& vector, const CL_Vec2f& normal) const;

	std::vector<Particle> particles;
	std::list<Line> lines;
	std::map<const Particle*, const Line*> slides;

	ParticleRegistry registry;
	Integrator integrator;

	GravityGenerator gravity;
	ThrustGenerator engine;
	ThrustGenerator explosion;
	DragGenerator drag;
	SpringGenerator spring;
	SpringPairGenerator springPair;

	float total;
	bool hasExploded;
};