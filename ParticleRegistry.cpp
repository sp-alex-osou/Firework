#include "ParticleRegistry.h"


ParticleRegistry::ParticleRegistry(void)
{
}


ParticleRegistry::~ParticleRegistry(void)
{
}


void ParticleRegistry::subscribe(const Particle& particle, const ForceGenerator& forceGenerator)
{
	registry[&particle].push_back(&forceGenerator);
}


void ParticleRegistry::unsubscribe(const Particle& particle, const ForceGenerator& forceGenerator)
{
	registry[&particle].remove(&forceGenerator);
}


const std::list<const ForceGenerator*>& ParticleRegistry::getForceGenerators(const Particle& particle) const
{
	const Particle* p = &particle;

	std::map<const Particle*, std::list<const ForceGenerator*>>::const_iterator it = registry.find(&particle);

	if (it != registry.end())
		return it->second;

	throw std::exception("particle not found");
}