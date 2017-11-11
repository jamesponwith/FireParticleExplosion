//
//  Swarm.h
//  FireExplosion
//
//  Created by James Ponwith on 10/28/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//

#ifndef Swarm_h
#define Swarm_h

#include <SDL2/SDL.h>
#include "Particle.h"

namespace booya {
    
class Swarm {
public:
    const static int NPARTICLES = 5000;
private:
    Particle *m_pParticles;
    int lastTime;
public:
    Swarm();
    virtual ~Swarm();
    void update(int elapsed);
    
const Particle * const getParticles() {
        return m_pParticles;
};
    
}; /* Swarm class */
} /* namespace booya */
#endif /* Swarm_h */
