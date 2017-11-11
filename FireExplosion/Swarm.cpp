//
//  Swarm.cpp
//  FireExplosion
//
//  Created by James Ponwith on 10/28/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//

#include "Swarm.h"

namespace booya {
    
    Swarm::Swarm(): lastTime(0) {
        m_pParticles = new Particle[NPARTICLES];
        
    }
    
    void Swarm::update(int elapsed) {
        
        int interval = elapsed - lastTime; 
        
        for(int i = 0; i < Swarm::NPARTICLES; i++){
            m_pParticles[i].update(interval);
        }
        
        lastTime = elapsed;
    }

    Swarm::~Swarm() {
        delete [] m_pParticles;
    }
} /* namespace booya */
