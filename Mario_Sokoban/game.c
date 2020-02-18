//
//  game.c
//  Main game function that runs the mario sokoban game
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
#include "game.h"

void game(SDL_Window* window){

    // Variable initialization
    SDL_Surface *mario[4] = {NULL}; // 4 surfaces for 4 Mario directions
    SDL_Surface* wall = NULL;
    SDL_Surface* crate = NULL;
    SDL_Surface* crateOK = NULL;
    SDL_Surface* objective = NULL;
    SDL_Surface* marioCurr = NULL;
    SDL_Rect position, positionPlayer;
    SDL_Event event;
    int play = 1, objectivesLeft = 0, i = 0, j = 0;
    int map[NB_BLOCKS_WIDTH][NB_BLOCKS_HEIGHT] = {0};
    
    // Generate pointer to window surface
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    // Sprites loading
    wall = IMG_Load("sprites_mario_sokoban/mur.jpg");
    crate = IMG_Load("sprites_mario_sokoban/caisse.jpg");
    crateOK = IMG_Load("sprites_mario_sokoban/caisse_ok.jpg");
    objective = IMG_Load("sprites_mario_sokoban/objectif.png");
    mario[DOWN] = IMG_Load("sprites_mario_sokoban/mario_bas.gif");
    mario[LEFT] = IMG_Load("sprites_mario_sokoban/mario_gauche.gif");
    mario[UP] = IMG_Load("sprites_mario_sokoban/mario_haut.gif");
    mario[RIGHT] = IMG_Load("sprites_mario_sokoban/mario_droite.gif");

    // Current Mario initialization
    marioCurr = mario[DOWN]; // Mario down is loaded first
    
    // Loading level check
    if (!loadLevel(map)){
        fprintf(stderr, "Cannot load map in game.c\n");
        exit(EXIT_FAILURE);
    }
    
    // Seeking start mario position
    for (i = 0; i < NB_BLOCKS_WIDTH; i++){
        for (j = 0; j < NB_BLOCKS_HEIGHT; j++){
            if (map[i][j] == MARIO){
                positionPlayer.x = i;
                positionPlayer.y = j;
                map[i][j] = VOID;
                i = NB_BLOCKS_WIDTH;
                j = NB_BLOCKS_HEIGHT;
            }
        }
    }
    
    // Main play loop
    while (play){
        SDL_WaitEvent(&event);
        // Test for event
        switch (event.type){
            case SDL_QUIT:
                play = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        play = 0;
                        break;
                    case SDLK_UP:
                        marioCurr = mario[UP];
                        movePlayer(map, &positionPlayer, UP);
                        break;
                    case SDLK_DOWN:
                        marioCurr = mario[DOWN];
                        movePlayer(map, &positionPlayer, DOWN);
                        break;
                    case SDLK_RIGHT:
                        marioCurr = mario[RIGHT];
                        movePlayer(map, &positionPlayer, RIGHT);
                        break;
                    case SDLK_LEFT:
                        marioCurr = mario[LEFT];
                        movePlayer(map, &positionPlayer, LEFT);
                        break;
                }
                break;
        }
        
        // Erase screen with blue background
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 219, 252, 255));
        
        // Initialize objective left counter
        objectivesLeft = 0;
        
        // Position elements on screen
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
                    case CRATE_OK:
                        SDL_BlitSurface(crateOK, NULL, screen, &position);
                        break;
                    case OBJECTIVE:
                        SDL_BlitSurface(objective, NULL, screen, &position);
                        objectivesLeft = 1;
                        break;
                }
            }
        }
        
        // Test for objectives left
        if (!objectivesLeft){
            play = 0;
        }
        
        // Blit mario at new location
        position.x = positionPlayer.x * SIZE_BLOCK;
        position.y = positionPlayer.y * SIZE_BLOCK;
        SDL_BlitSurface(marioCurr, NULL, screen, &position);
        
        // Update window
        if (play){
        SDL_UpdateWindowSurface(window);
        }
    }
    
    // Free loaded surfaces
    SDL_FreeSurface(wall);
    SDL_FreeSurface(crate);
    SDL_FreeSurface(crateOK);
    SDL_FreeSurface(objective);
    for (i = 0; i < 4; i++){
        SDL_FreeSurface(mario[i]);
    }
}

void movePlayer(int map[][NB_BLOCKS_HEIGHT], SDL_Rect *pos, int direction){
    
    // Direction switch
    switch (direction){
        case UP:
            /*
             Clash tests for UP move:
             1. Check for map limit above
             2. Check for wall above
             3. Check for crate and wall or double crate above
             */
            if (pos->y - 1 < 0){
                break;
            }
            if (map[pos->x][pos->y - 1] == WALL){
                break;
            }
            if ((map[pos->x][pos->y - 1] == CRATE || map[pos->x][pos->y - 1] == CRATE_OK) && (pos->y - 2 < 0 || map[pos->x][pos->y - 2] == WALL || map[pos->x][pos->y - 2] == CRATE || map[pos->x][pos->y - 2] == CRATE_OK)){
                break;
            }
            // Check for a crate to move UP
            moveCrate(&map[pos->x][pos->y - 1], &map[pos->x][pos->y - 2]);
            // Player can move UP
            pos->y--;
            break;
        case DOWN:
            /*
             Clash tests for DOWN move:
             1. Check for map limit below
             2. Check for wall below
             3. Check for crate and wall or double crate below
             */
            if (pos->y + 1 > NB_BLOCKS_HEIGHT){
                break;
            }
            if (map[pos->x][pos->y + 1] == WALL){
                break;
            }
            if ((map[pos->x][pos->y + 1] == CRATE || map[pos->x][pos->y + 1] == CRATE_OK) && (pos->y + 2 > NB_BLOCKS_HEIGHT || map[pos->x][pos->y + 2] == WALL || map[pos->x][pos->y + 2] == CRATE || map[pos->x][pos->y + 2] == CRATE_OK)){
                break;
            }
            // Check for crate to move DOWN
            moveCrate(&map[pos->x][pos->y + 1], &map[pos->x][pos->y + 2]);
            // Player can move DOWN
            pos->y++;
            break;
        case RIGHT:
            /*
             Clash tests for RIGHT move:
             1. Check for map limit on the right
             2. Check for wall on the right
             3. Check for crate and wall or double crate on the right
             */
            if (pos->x + 1 > NB_BLOCKS_WIDTH){
                break;
            }
            if (map[pos->x + 1][pos->y] == WALL){
                break;
            }
            if ((map[pos->x + 1][pos->y] == CRATE || map[pos->x + 1][pos->y] == CRATE_OK) && (pos->x + 2 > NB_BLOCKS_WIDTH || map[pos->x + 2][pos->y] == WALL || map[pos->x + 2][pos->y] == CRATE || map[pos->x + 2][pos->y] == CRATE_OK)){
                break;
            }
            // Check for a crate to move RIGHT
            moveCrate(&map[pos->x + 1][pos->y], &map[pos->x + 2][pos->y]);
            // Player can move RIGHT
            pos->x++;
            break;
        case LEFT:
            /*
             Clash tests for LEFT move:
             1. Check for map limit on the left
             2. Check for wall on the left
             3. Check for crate and wall or double crate on the left
             */
            if (pos->x - 1 < 0){
                break;
            }
            if (map[pos->x - 1][pos->y] == WALL){
                break;
            }
            if ((map[pos->x - 1][pos->y] == CRATE || map[pos->x - 1][pos->y] == CRATE_OK) && (pos->x - 2 < 0 || map[pos->x - 2][pos->y] == WALL || map[pos->x - 2][pos->y] == CRATE || map[pos->x - 2][pos->y] == CRATE_OK)){
                break;
            }
            // Check for a crate to move LEFT
            moveCrate(&map[pos->x - 1][pos->y], &map[pos->x - 2][pos->y]);
            // Player can move LEFT
            pos->x--;
            break;
    }
}

void moveCrate(int *firstBlock, int *secondBlock){
    
    // Move crate from first to second
    if (*firstBlock == CRATE || *firstBlock == CRATE_OK){
        if (*secondBlock == OBJECTIVE){
            *secondBlock = CRATE_OK;
        }
        else{
            *secondBlock = CRATE;
        }
        if (*firstBlock == CRATE_OK){
            *firstBlock = OBJECTIVE;
        }
        else{
            *firstBlock = VOID;
        }
    }
}
