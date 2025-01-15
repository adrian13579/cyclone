#include "core.h"

namespace cyclone {
    /** A particle is the simplest object that can be simulated in the physics system. **/
    class Particle 
    {
        public:
            /** Holds the linear position of the particle in world space. **/
            Vector3 position;

            /** Holds the linear velocity of the particle in world space. **/
            Vector3 velocity;

            /** Holds the acceleration of the particle. **/
            Vector3 acceleration;
    };
}