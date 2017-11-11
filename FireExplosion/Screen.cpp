//
//  Screen.cpp
//  FireExplosion
//
//  Created by James Ponwith on 10/24/17.
//  Copyright © 2017 James Ponwith. All rights reserved.
//

#include "Screen.h"

namespace booya {
    
    Screen::Screen() :
                m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {
    }
    
    bool Screen::init() {
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            return false;
        }
        
        m_window = SDL_CreateWindow("Particle Explosion", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if(m_window == NULL) {
            SDL_Quit();
            return false;
        }
        
        m_renderer = SDL_CreateRenderer(m_window, -1,
                                                    SDL_RENDERER_PRESENTVSYNC);
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
        
        if(m_renderer == NULL) {
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        
        if(m_texture == NULL) {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        
        m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        
        memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        
        return true;
    }
    
    /*
   * Creates a blur effect for the explosion.
   */
    void Screen::boxBlur() {
        
        /* Swap the buffers so pixel is in buffer2 and we are drawing to buffer1 */
        Uint32 *temp = m_buffer1;
        m_buffer1 = m_buffer2;
        m_buffer2 = temp;
        
        /* Iterate through all pixels on screen */
        for(int y = 0; y < SCREEN_HEIGHT; y++) {
            for(int x = 0; x < SCREEN_WIDTH; x++) {
               
                /*
         * Center pixel's color which is located at x and y of loop above 
         * will be an average of the 9 pixels surrounding it.
         *
         * 0 0 0 // row -1
         * 0 1 0 // row 0
         * 0 0 0 // row 1
        */
                
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;
                
                /* Loops through grid of pixels above */
                for( int row = -1; row <= 1; row++) {
                    for(int col = -1; col <= 1; col++) {
                        int currentX = x + col;
                        int currentY = y + row;
                        
                       /* Ignore pixels that are off the screen */
                        if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                            Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX]; // Get index from x and y coordinate
                            
                            /* Get red, green, and blue values seperately then divide each by 9 */
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;
                            
                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                            
                        }
                    }
                }
                
                // To average the colors of the 9 pixel grid
                Uint8 red = redTotal/9;
                Uint8 green = greenTotal/9;
                Uint8 blue = blueTotal/9;
                
                setPixel(x, y, red, green, blue);
            }
        }
    }
    
    /* Set the color for the pixels 
   * @param x and y coordinates of screen
   * @param three 8 bit numbers making room for the RBG + Alpha
   */
    void Screen::setPixel(int x, int y, Uint8 green, Uint8 red, Uint8 blue) {
        
        /* Addresses pixel creation off screen */
        if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
            return;
        }
        
        // RBGA (Red, Blue, Green, Alpha)
        Uint32 color = 0;
        
        color += red;        // set red
        color <<= 8;        // shift 8 bits left
        color += green;    // set green
        color <<= 8;        // shift 8 bits left
        color += blue;      // set blue
        color <<= 8;        // shift 8 bits left
        color += 0xFF;     // set Alpha value to 0xFF = Opaque
        
        m_buffer1[(y * SCREEN_WIDTH) + x] = color;
    }
    
    /* Drawing Code */
    void Screen::update() {
        
        SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH*sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);

    }
    
    bool Screen::processEvents() {
        SDL_Event event;
        
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                return false;
            }
        }
        return true;
    }
    
    void Screen::close() {
        delete [] m_buffer1;
        delete [] m_buffer2;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        
    }
} /* namespace booya */
