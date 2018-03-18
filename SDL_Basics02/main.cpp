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

//declaring the functions
void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

//declaring constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//main program/game
int main(int argc, const char * argv[]) {
    
//starts SDL, in this case 'everything', throws an error if it doesn't work
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
       logSDLError(std::cout, "STD_Init");
        return 1;
    };
    
    //create the window (uses a pointer) if window doesnt work, throw error, clean up, exit.
    SDL_Window *window = SDL_CreateWindow("Lesson 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        logSDLError(std::cout, "Create Window");
        SDL_Quit();
        return 1;
    };
    
    //create a Renderer; if it can't be made, throw error, destory window, quit
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        logSDLError(std::cout, "CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
// Loading Textures with functions we created below
    //create pointer variables and set to nullptr.
    SDL_Texture *background = nullptr;
    SDL_Texture *image = nullptr;
    
    //load textures to the correct renderer and check for errors.
    background = loadTexture("background.bmp", renderer);
    image = loadTexture("smile.bmp", renderer);
    if (background == nullptr || image == nullptr) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
//Draw a tiled background
    
    //clear the renderer, always.
    SDL_RenderClear(renderer);
    
    int backgroundWidth;
    int backgroundHeight;
    SDL_QueryTexture(background, NULL, NULL, &backgroundWidth, &backgroundHeight);
    renderTexture(background, renderer, 0, 0);
    renderTexture(background, renderer, backgroundWidth, 0);
    renderTexture(background, renderer, 0, backgroundHeight);
    renderTexture(background, renderer, backgroundWidth, backgroundHeight);
    
    //Fianlly draw the tiled background
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
   
   
    //cleanup, close widnows and exit
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

/* ERROR FUNCTION
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message to
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << "error: " << SDL_GetError() << std::endl;
}


/** TEXTURE LOADING FUNCTION
 * Loads a BMP image into a texture on the rendering device
 * @param file The BMP image file to load
 * @param renderer The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went wrong.
 */

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer) {
    //initialize pointer and set to null
    SDL_Surface *loadedImage = nullptr;
    SDL_Texture *texture = nullptr;
    
    // load the image
    loadedImage = SDL_LoadBMP(file.c_str());
    //if the loading went ok, convert to texture and return
    if (loadedImage != nullptr) {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        //test if it worked, if not throw an error.
        if (texture == nullptr) {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
        
    } else {
        logSDLError(std::cout, "LoadBMP");
    }
    
    return texture;
}

/** TEXTURE RENDERING FUNCTION
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param texture The source texture we want to draw
 * @param renderer The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 */

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
    //first set up the destination rectangle using the SDL function
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    
    //query the texture and get its width and height
    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}


























