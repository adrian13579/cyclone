#include <iostream>
#include "../include/cyclone/core.h"

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    cyclone::Vector3 vector1(1, 2, 3);

    cyclone::real a = vector1.magnitude();

    vector1.invert();
    vector1.normalize();

    vector1 += vector1;


    std::cout << "Magnitude: " << a << std::endl;
    return 0;
}