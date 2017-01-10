//
//  SteeredParticle.cpp
//  myEnthusiasticSketch
//
//  Created by Hannah Liao on 4/25/16.
//
//

#include "ofMath.h"
#include "Particle.h"
#include "SteeredParticle.h"



void SteeredParticle::addForce(const ofVec3f vec)
{
    steeringForce += vec;
}

void SteeredParticle::update()
{
    steeringForce.limit(maxForce);
    steeringForce *= (float)1 / mass;
    velocity += steeringForce;
    Particle::update();
    steeringForce.set(0, 0, 0);
}
// looking for the neighbor
void SteeredParticle::seek(const ofVec3f& target)
{
    ofVec3f desiredVelocity;
    desiredVelocity.set(target);
    desiredVelocity -= position;
    desiredVelocity.normalize();
    desiredVelocity *= maxSpeed;
    steeringForce += (desiredVelocity - velocity);
}

// the object runs away from each other if it is too closed
void SteeredParticle::flee(const ofVec3f& target)
{
    ofVec3f desiredVelocity;
    desiredVelocity.set(target);
    desiredVelocity -= position;
    
    // if target position and this vehicle position is the same,
    // vehicle runs away to random vector.
    if (desiredVelocity.length() == 0) {
        desiredVelocity = getRandVec();
    }
    
    desiredVelocity.normalize();
    desiredVelocity *= maxSpeed;
    steeringForce -= (desiredVelocity - velocity);
}

void SteeredParticle::arrive(const ofVec3f& target)
{
    float arrivalThreshold = maxSpeed * 10;
    
    ofVec3f desiredVelocity;
    desiredVelocity.set(target);
    desiredVelocity -= position;
    desiredVelocity.normalize();
    
    float dist = position.distance(target);
    if (dist > arrivalThreshold) desiredVelocity *= maxSpeed;
    else desiredVelocity *= (float)maxSpeed * dist / arrivalThreshold;
    
    steeringForce += desiredVelocity - velocity;
}

void SteeredParticle::pursue(const Particle& target)
{
    float lookAheadTime = (float)position.distance(target.position) / maxSpeed;
    
    ofVec3f targetVelocity;
    targetVelocity.set(target.velocity);
    targetVelocity *= lookAheadTime;
    
    ofVec3f predictedTarget;
    predictedTarget.set(target.position);
    predictedTarget += targetVelocity;
    
    seek(predictedTarget);
}

void SteeredParticle::evade(const Particle& target)
{
    float lookAheadTime = (float)position.distance(target.position) / maxSpeed;
    
    ofVec3f targetVelocity;
    targetVelocity.set(target.velocity);
    targetVelocity *= lookAheadTime;
    
    ofVec3f predictedTarget;
    predictedTarget.set(target.position);
    predictedTarget -= targetVelocity;
    
    flee(predictedTarget);
}

ofVec3f SteeredParticle::getOffset()
{
    
    float a1 = (float)(wanderAngle1 * PI / 180);
    float a2 = (float)(wanderAngle2 * PI / 180);
    
    ofVec3f offset;
    offset.x = (float)(wanderRadius * sin(a1) * cos(a2));
    offset.y = (float)(wanderRadius * sin(a1) * sin(a2));
    offset.z = (float)(wanderRadius * cos(a1));
    //offset *= wanderRadius;
    
    wanderAngle1 += (float)(ofRandom(0, wanderRange) - (float)wanderRange * .5f);
    wanderAngle2 += (float)(ofRandom(0, wanderRange) - (float)wanderRange * .5f);
    
    return offset;
}

void SteeredParticle::wander()
{
    ofVec3f center;
    ofVec3f offset;
    
    center.set(velocity);
    center.normalize();
    center *= wanderDistance;
    offset = getOffset();
    
    steeringForce += center + offset;
}



void SteeredParticle::patrol(const vector<ofVec3f> paths)
{
    bool last = pathIndex >= paths.size() - 1;
    
    if (position.distance(paths[pathIndex]) < pathThreshold)
    {
        if (last && pathLoop) pathIndex = 0;
        else if (!last) pathIndex++;
    }
    
    if (last && !pathLoop) arrive(paths[pathIndex]);
    else seek(paths[pathIndex]);
}

/*
 void SteeredVehicle::avoid()
 {
	
 }*/

void SteeredParticle::randomWalk()
{
    float a1 = (float)(ofRandom(0, 360) * PI / 180);
    float a2 = (float)(ofRandomuf() * 2 * PI);
    
    ofVec3f desiredVelocity;
    desiredVelocity.x = (float)(sin(a1) * cos(a2));
    desiredVelocity.y = (float)(sin(a1) * sin(a2));
    desiredVelocity.z = (float)(cos(a1));
    desiredVelocity.normalize();
    desiredVelocity *= maxSpeed;
    steeringForce += (desiredVelocity - velocity);
}

bool SteeredParticle::inSight(const ofVec3f& target)
{
    if (position.distance(target) > inSightDist) return false;
    
    ofVec3f heading;
    heading.set(velocity);
    heading.normalize();
    
    ofVec3f difference;
    difference.set(target);
    difference -= position;
    
    if (difference.dot(heading) < 0) return false;
    return true;
}

bool SteeredParticle::tooClose(const ofVec3f& target)
{
    return position.distance(target) < tooCloseDist;
}

ofVec3f SteeredParticle::getRandVec()
{
    ofVec3f vec;
    
    float a1 = (float)(ofRandom(0, 360) * PI / 180);
    float a2 = (float)(ofRandomuf() * 2 * PI);
    
    vec.x = (float)(sin(a1) * cos(a2));
    vec.y = (float)(sin(a1) * sin(a2));
    vec.z = (float)(cos(a1));
    
    return vec;
}