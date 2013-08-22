#pragma once

#include <list>
#include <set>

#include "ForceGenerator.h"
#include "Particle.h"

class ParticleRegistry
{
public:
	ParticleRegistry(void);
	~ParticleRegistry(void);

	void subscribe(const Particle& particle, const ForceGenerator& forceGenerator);
	void unsubscribe(const Particle& particle, const ForceGenerator& forceGenerator);

	const std::list<const ForceGenerator*>& getForceGenerators(const Particle& particle) const;
private:
	std::map<const Particle*, std::list<const ForceGenerator*>> registry;
};

