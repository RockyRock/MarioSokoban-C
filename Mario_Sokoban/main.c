//
//  main.m
//  Main function running Mario sokoban game
//  Mario_Sokoban
//
//  Created by Romain GUICHERD on 09/01/2020.
//  Copyright © 2020 Romain GUICHERD. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "constants.h"
#include "game.h"
#include "editor.h"

int main(int argc, char *argv[]) {
    
    // Declare pointers and position variable
    SDL_Window *window = NULL;
    SDL_Surface *menu = NULL;
    SDL_Event e;
    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;
    
    // Initialize SDL2 and check for issues
    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        fprintf(stderr, "Error in opening SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Mario Sokoban",                   // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        WIDTH_WINDOW,                      // width in pixels
        HEIGHT_WINDOW,                     // height in pixels
        0//SDL_WINDOW_OPENGL                  // flags openGL
    );

    // Check that the window was successfully created
    if(window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Set window icon and load menu image
    SDL_SetWindowIcon(window, IMG_Load("sprites_mario_sokoban/caisse.jpg"));
    menu = IMG_Load("sprites_mario_sokoban/menu.jpg");
    
    // Generate pointer to window surface
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    // SDL event to run
    int quit = 0;
    while(!quit){
        SDL_WaitEvent(&e);
        switch(e.type){
            case SDL_QUIT:              // Quit the game
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE:   // Quit the game
                        quit = 1;
                        break;
                    case SDLK_1:        // Start the game
                        game(window);
                        break;
                    case SDLK_2:        // Launch level editor
                        editor(window);
                        break;
                }
                break;
        }
        
        // Fill SDL window screen with RGB color and blit menu
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, screen, &positionMenu);
        
        // Update SDL window
        SDL_UpdateWindowSurface(window);
    }
    
    // Free menu and destroy the window
    SDL_FreeSurface(menu);
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    
    // Function return
    return EXIT_SUCCESS;
}
