//
//  main.cpp
//  SDL_Basics02
//
// http://www.willusher.io/pages/sdl2/
//  Created by Developer on 3/16/18.
//  Copyright © 2018 Developer. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, const char * argv[]) {
    
    
//starts SDL, in this case everything, throws an error if it doesn't work
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error initializing: " << SDL_GetError() << std::endl;
        return 1;
    };
    
    //create the window (pointer) if window doesnt work, throw error, clean up, exit.
    SDL_Window *window = SDL_CreateWindow("Hello Everybody", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        std::cout << "Something screwed up: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    };
    
    //create a Renderer; if it can't be made, throw error, destory window, quit
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == NULL) {
            SDL_DestroyWindow(window);
            std::cout << "Something got jacked" << SDL_GetError() << std::endl;
            SDL_Quit();
        return 1;
    }
    
    //loading the image; SDL_LoadBMP -> SDL_Surface* -> SDL_Texture
    //SDL_LeadBMP takes file path and gives us an SDL_Surface to use (or NULL)
    
    SDL_Surface *imageSurface = SDL_LoadBMP("Calcifer.bmp");
    if (imageSurface == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        std::cout << "Couldn't Load the BitMap" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    //We take the SDL_Surface and create a texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (texture == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        std::cout << "Couldn't load texture made from bitmap: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
        
    }
    
    //Fianlly draw the dang thiing
    //render it three times then stop, suing a for loop
    for (int i = 0; i < 3; i++) {
        //first we clear the renderer
        SDL_RenderClear(renderer);
        //draw the texture (converted bitmap) on the unseen buffer
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        //update the screen user sees
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    
    return 0;
}
