//
//  Particle.h
//  FireExplosion
//
//  Created by James Ponwith on 10/28/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//

#ifndef Particle_h
#define Particle_h

#include <SDL2/SDL.h>

namespace booya {
    
    /* struct's defualt variables are public vs class which are private */
    struct Particle {

        double m_x;
        double m_y;
        
    private:
        double m_speed;
        double m_direction;
        
    private:
        void init();
        
    public:
        Particle();
        virtual ~Particle();
        void update(int interval);
    };
    
} /* namespace booya*/

#endif /* Particle_h */
