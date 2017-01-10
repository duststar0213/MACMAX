//
//  SteeredParticle.hpp
//  myEnthusiasticSketch
//
//  Created by Hannah Liao on 4/25/16.
//
//

#ifndef SteeredParticle_hpp
#define SteeredParticle_hpp

#include <stdio.h>
#include "Particle.h"
#include "ofMath.h"
#include "ofVec3f.h"

class SteeredParticle : public Particle {
    
private:
    
    float wanderAngle1;
    float wanderAngle2;
    
    
protected:
    
    ofVec3f steeringForce;
    ofVec3f getOffset();
    ofVec3f getRandVec();
    
    
public:
    
    float maxForce;
    float wanderDistance;
    float wanderRadius;
    float wanderRange;
    float inSightDist;
    float tooCloseDist;
    float pathThreshold;
    bool pathLoop;
    int pathIndex;
    
    
    SteeredParticle(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : Particle(_x, _y, _z)
    {
        maxForce = 1.0f;
        wanderAngle1 = ofRandom(0.0f, 360.0f);
        wanderAngle2 = ofRandom(0.0f, 360.0f);
        wanderDistance = 10.0f;
        wanderRadius = 5.0f;
        wanderRange = 10.0f;
        pathIndex = 0;
        pathThreshold = 20.0f;
        pathLoop = false;
        inSightDist = 120.0f;
        tooCloseDist = 20.0f;
    }
    
    
    void addForce(const ofVec3f vec);
    void update();
    void seek(const ofVec3f& target);
    void flee(const ofVec3f& target);
    void arrive(const ofVec3f& target);
    void pursue(const Particle& target);
    void evade(const Particle& target);
    void wander();
    void patrol(const vector<ofVec3f> paths);
    //void avoid();
    void randomWalk();
    bool inSight(const ofVec3f& target);
    bool tooClose(const ofVec3f& target);
    
    
    template<typename Type> void flock(vector<Type>& particles)
    {
        ofVec3f averageVelocity;
        ofVec3f averagePosition;
        int inSightCnt = 0;
        
        averageVelocity.set(velocity);
        
        for (int i = 0; i < particles.size(); i++)
        {
            if (particles[i].getId() == getId()) continue;
            if (!inSight(particles[i].position)) continue;
            
            averageVelocity += particles[i].velocity;
            averagePosition += particles[i].position;
            inSightCnt++;
            
            if (tooClose(particles[i].position))
            {
                flee(particles[i].position);
            }
        }
        
        if (inSightCnt > 0)
        {
            averagePosition *= 1.0f / inSightCnt;
            seek(averagePosition);
            averageVelocity *= 1.0f / inSightCnt;
            steeringForce += averageVelocity - velocity;
        }
    }
};




#endif /* SteeredParticle_hpp */
