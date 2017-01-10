//
//  boid.h
//  myDesirableSketch
//
//  Created by Hannah Liao on 4/26/16.
//
//

#ifndef boid_h
#define boid_h



class Boid{
    
public:
    
    ofVec2f position, target;
    bool alive;
    vector<Boid *> neighbors;
    
    //
    // these pure virtual functions must be overridden in the derived class
    //
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual void link(Boid *ref){
        // push a pointer onto the neighbors vector
        neighbors.push_back(ref);
    }
};

#endif

#endif /* boid_h */
