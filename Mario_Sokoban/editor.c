//
//  editor.c
//  Editor function to create new maps
//  Mario_Sokoban
//
//  Created by Romain GUICHERD on 25/01/2020.
//  Copyright © 2020 Romain GUICHERD. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "constants.h"
#include "files.h"
#include "editor.h"

void editor(SDL_Window* window){
    
    // Variable initialization
    SDL_Surface *wall = NULL;
    SDL_Surface *crate = NULL;
    SDL_Surface *objective = NULL;
    SDL_Surface *mario = NULL;
    SDL_Surface *crateOK = NULL;
    SDL_Rect position;
    SDL_Event event;
    
    int edit = 1, leftClick = 0, rightClick = 0;
    int currEl = WALL, i = 0, j = 0;
    int x = 0, y = 0;
    int player = 0;
    int map[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT] = {0};
    
    // Generate pointer to window surface
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    // Sprites loading
    wall = IMG_Load("sprites_mario_sokoban/mur.jpg");
    crate = IMG_Load("sprites_mario_sokoban/caisse.jpg");
    objective = IMG_Load("sprites_mario_sokoban/objectif.png");
    mario = IMG_Load("sprites_mario_sokoban/mario_bas.gif");
    crateOK = IMG_Load("sprites_mario_sokoban/caisse_ok.jpg");
    
    // Loading level check
    if (!loadLevel(map)){
        fprintf(stderr, "Cannot load map in editor.c\n");
        exit(EXIT_FAILURE);
    }
    
    // Editor loop
    while (edit){
        SDL_WaitEvent(&event);
        // Test for events
        switch (event.type){
            case SDL_QUIT:
                edit = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Check if there is already a Mario on the map
                player = 0;
                for (i = 0; i < NB_BLOCKS_WIDTH; i++){
                    for (j = 0; j < NB_BLOCKS_HEIGHT; j++){
                        if (map[i][j] == MARIO){
                            player = 1;
                            i = NB_BLOCKS_WIDTH;
                            j = NB_BLOCKS_HEIGHT;
                        }
                    }
                }
                if (event.button.button == SDL_BUTTON_LEFT){
                    if (currEl != MARIO || !player){
                        map[event.button.x / SIZE_BLOCK][event.button.y / SIZE_BLOCK] = currEl;
                        leftClick = 1;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT){
                    map[event.button.x / SIZE_BLOCK][event.button.y / SIZE_BLOCK] = VOID;
                    rightClick = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    leftClick = 0;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT){
                    rightClick = 0;
                }
                break;
            case SDL_MOUSEMOTION:
                if (leftClick && currEl != MARIO){
                    map[event.button.x / SIZE_BLOCK][event.button.y / SIZE_BLOCK] = currEl;
                }
                else if (rightClick){
                    map[event.button.x / SIZE_BLOCK][event.button.y / SIZE_BLOCK] = VOID;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        edit = 0;
                        break;
                    case SDLK_s:
                        saveLevel(map);
                        break;
                    case SDLK_c:
                        loadLevel(map);
                        break;
                    case SDLK_1:
                        currEl = WALL;
                        break;
                    case SDLK_2:
                        currEl = CRATE;
                        break;
                    case SDLK_3:
                        currEl = OBJECTIVE;
                        break;
                    case SDLK_4:
                        currEl = MARIO;
                        break;
                    case SDLK_5:
                        currEl = CRATE_OK;
                        break;
                }
                break;
        }
        
        // Erase screen with light blue background
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 219, 252, 255));
        
        // Blit element on map
        for (i = 0; i < NB_BLOCKS_WIDTH; i++){
            for (j = 0; j < NB_BLOCKS_HEIGHT; j++){
                position.x = i * SIZE_BLOCK;
                position.y = j * SIZE_BLOCK;
                switch (map[i][j]){
                    case WALL:
                        SDL_BlitSurface(wall, NULL, screen, &position);
                        break;
                    case CRATE:
                        SDL_BlitSurface(crate, NULL, screen, &position);
                        break;
                    case OBJECTIVE:
                        SDL_BlitSurface(objective, NULL, screen, &position);
                        break;
                    case MARIO:
                        SDL_BlitSurface(mario, NULL, screen, &position);
                        break;
                    case CRATE_OK:
                        SDL_BlitSurface(crateOK, NULL, screen, &position);
                        break;
                }
            }
        }
        
        // Mouse position block check
        SDL_GetMouseState(&x, &y);
        position.x = x / SIZE_BLOCK*SIZE_BLOCK;
        position.y = y / SIZE_BLOCK*SIZE_BLOCK;
        
        // Blit current selected element with 128 alpha transparency
        switch (currEl){
            case WALL:
                SDL_SetSurfaceBlendMode(wall, SDL_BLENDMODE_BLEND);
                SDL_SetSurfaceAlphaMod(wall, 128);
                SDL_BlitSurface(wall, NULL, screen, &position);
                SDL_SetSurfaceAlphaMod(wall, 255);
                break;
            case CRATE:
                SDL_SetSurfaceBlendMode(crate, SDL_BLENDMODE_BLEND);
                SDL_SetSurfaceAlphaMod(crate, 128);
                SDL_BlitSurface(crate, NULL, screen, &position);
                SDL_SetSurfaceAlphaMod(crate, 255);
                break;
            case OBJECTIVE:
                SDL_SetSurfaceBlendMode(objective, SDL_BLENDMODE_BLEND);
                SDL_SetSurfaceAlphaMod(objective, 128);
                SDL_BlitSurface(objective, NULL, screen, &position);
                SDL_SetSurfaceAlphaMod(objective, 255);
                break;
            case MARIO:
                SDL_SetSurfaceBlendMode(mario, SDL_BLENDMODE_BLEND);
                SDL_SetSurfaceAlphaMod(mario, 128);
                SDL_BlitSurface(mario, NULL, screen, &position);
                SDL_SetSurfaceAlphaMod(mario, 255);
                break;
            case CRATE_OK:
                SDL_SetSurfaceBlendMode(crateOK, SDL_BLENDMODE_BLEND);
                SDL_SetSurfaceAlphaMod(crateOK, 128);
                SDL_BlitSurface(crateOK, NULL, screen, &position);
                SDL_SetSurfaceAlphaMod(crateOK, 255);
                break;
        }
        
        // Update window
        if (edit){
        SDL_UpdateWindowSurface(window);
        }
    }
    
    // Free loaded surface
    SDL_FreeSurface(wall);
    SDL_FreeSurface(crate);
    SDL_FreeSurface(objective);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(crateOK);
}
