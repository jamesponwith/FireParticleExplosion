//
//  Particle.cpp
//  FireExplosion
//
//  Created by James Ponwith on 10/28/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//

#include "Particle.h"
#include <math.h>
#include <stdlib.h>


namespace booya {
    
    /* Setting x and y coordinates to zero to begin explosion
   * in the center of the screen. 
   */
    Particle::Particle(): m_x(0), m_y(0) {
        init();
      }

    /* 
   * Calculate how much to move x and y coordinates
   */
    void Particle::update(int interval) {
        
        m_direction += interval * 0.0003;
        double xspeed = m_speed * cos(m_direction);
        double yspeed = m_speed * sin(m_direction);
        
        m_x += xspeed * interval;
        m_y += yspeed * interval;
        
        /* If particles move out of screen bounds, reinitialize */
        if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
            init();
        }
        
        if(rand() < RAND_MAX/100) {
            init();
        }
    }
    
    /*
   * Initializes particles with random directions and speeds
   */
    void Particle::init() {
        m_x = 0;
        m_y = 0;
        m_direction = (2 * M_PI * rand()) / RAND_MAX;
        m_speed = (0.05 * rand()) / RAND_MAX;
        
        m_speed *= m_speed;
    }
    
    Particle::~Particle() {
        
    }
    
} /* namespace booya */
