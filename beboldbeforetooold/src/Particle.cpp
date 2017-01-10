//
//  Particle.cpp
//  myEnthusiasticSketch
//
//  Created by Hannah Liao on 4/25/16.
//
//

#include "Particle.h"
#include <iostream>
#include "ofMath.h"

int Particle::number = 0;


void Particle::update()
{
    velocity.limit(maxSpeed);
    position += velocity;
    
    trails.push_back(position);
    if (trails.size() > maxTrailSize) trails.erase(trails.begin());
}
//bounce around according to the rule
void Particle::bounce(int w, int h, int d)
{
    if (position.x > w * .5f)
    {
        position.x = w * .5f;
        velocity.x *= -1;
    }
    else if (position.x < - w * .5f)
    {
        position.x = - w * .5f;
        velocity.x *= -1;
    }
    
    if (position.y > h * .5f)
    {
        position.y = h * .5f;
        velocity.y *= -1;
    }
    else if (position.y < - h * .5f)
    {
        position.y = - h * .5f;
        velocity.y *= -1;
    }
    
    if (position.z > d * .5f)
    {
        position.z = d * .5f;
        velocity.z *= -1;
    }
    else if (position.z < - d * .5f)
    {
        position.z = - d * .5f;
        velocity.z *= -1;
    }
}

void Particle::wrap(int w, int h, int d)
{
    if (position.x > w * .5f)
    {
        position.x = - w * .5f;
    }
    else if (position.x < - w * .5f)
    {
        position.x = w * .5f;
    }
    
    if (position.y > h * .5f)
    {
        position.y = - h * .5f;
    }
    else if (position.y < - h * .5f)
    {
        position.y = h * .5f;
    }
    
    if (position.z > d * .5f)
    {
        position.z = - d * .5f;
    }
    else if (position.z < - d * .5f)
    {
        position.z = d * .5f;
    }
}