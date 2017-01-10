//
//  Particle.hpp
//  myEnthusiasticSketch
//
//  Created by Hannah Liao on 4/25/16.
//
//

#ifndef Particle_h
#define Particle_h

#include <stdio.h>
#include "ofVec3f.h"


class Particle{
    
private:
    
    static int number;
    
    // instance identifier
    int id;
    
    
public:
    
    ofVec3f position;
    ofVec3f velocity;
    vector<ofVec3f> trails;
    
    float mass; // follow the gravity
    float maxSpeed; // follow the maxSpeed
    float maxTrailSize; // the number of boids you draw
    
    Particle(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) // make the new particle at 
    {
        id = number++;
        mass = 1.0f;
        maxSpeed = 4.0f;
        maxTrailSize = 10;
        position.set(ofVec3f(_x, _y, _z));
    }
    
    int getId() { return id; }
    
    void update();
    void bounce(int w, int h, int d);
    void wrap(int w, int h, int d);
};

#endif

