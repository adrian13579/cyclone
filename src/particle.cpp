#include <assert.h>
#include "../include/cyclone/particle.h"

using namespace cyclone;

void Particle::integrate(real duration)
{
    assert(duration > 0.0);

    position += velocity * duration;

    Vector3 resultingAcc = acceleration;
    resultingAcc += forceAccum * inverseMass;

    velocity += resultingAcc * duration;

    velocity *= real_pow(damping, duration);
}


