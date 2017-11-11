//======================================================
//  main.cpp
//  FireExplosion
//
//  Created by James Ponwith on 10/21/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//
//  Creates an explosion of patricles spawning in the
//  center of screen. The swarm of particles burst out
//  creating a vortex while gradually changing colors.
//
//======================================================

#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace booya;


int main(int argc, char *argv[]) {
    
    Screen screen;
    
    if(screen.init() == false) {
        cout << "Error initializing SDL" << endl;
    }
    
    Swarm swarm;
    
    // Game Loop
    while(true) {
        
        int elapsed = SDL_GetTicks();
        
        swarm.update(elapsed);
        
        unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128); // max at 256 because = char capacity
        unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
        unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);
        
        const Particle * const pParticles = swarm.getParticles();
        double halfScreenWidth = Screen::SCREEN_WIDTH/2;
        double halfScreenHeight = Screen::SCREEN_HEIGHT/2;
        
        
        for(int i = 0; i < Swarm::NPARTICLES; i++){
            Particle particle = pParticles[i];
            
            int x = (particle.m_x + 1) *  halfScreenWidth;
            int y = particle.m_y * halfScreenWidth + halfScreenHeight;
            
            screen.setPixel(x, y, red, blue, green);
        }
        
        // Blur particles and leave trail
        screen.boxBlur();
        
        // Draw the screen
        screen.update();
        
        // Check for messages/events
        if(screen.processEvents() == false) {
            break;
        }
    }

    screen.close();
    
    return 0;
}

