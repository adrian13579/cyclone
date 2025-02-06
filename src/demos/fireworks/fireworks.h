#include "../../../include/cyclone/particle.h"
#include "../../app.h"

class Firework: public cyclone::Particle {
    public:
        unsigned type;
        cyclone::real age;
};

struct FireworkRule {
    unsigned type;
    cyclone::real minAge;
    cyclone::real maxAge;
    cyclone::Vector3 minVelocity;
    cyclone::Vector3 maxVelocity;
    cyclone::real damping;

    struct Payload {
        unsigned type;
        unsigned count;
    };

    unsigned payloadCount;
    Payload *payloads;
};

class FireworksDemo : public Application {
    public:
        FireworksDemo();
        //virtual const char* getTitle();
        virtual void initGraphics();
        //virtual void update();
        //virtual void display();
        //virtual void key(unsigned char key);
        //virtual void mouse(int button, int state, int x, int y);
}; 