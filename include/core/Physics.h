#ifndef PHYSICS_H
#define PHYSICS_H
#include <SFML/Graphics.hpp>

enum isApplied
{
	no,
	yes
};

class Physics {
private:
    float gravity = 9.81f;

public:
    Physics(float g) : gravity(g) {};

    void setGravity(float g);
    float getGravity() const;
};
#endif