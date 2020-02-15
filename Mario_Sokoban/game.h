//
//  game.h
//  Prototypes definition for game
//  Mario_Sokoban
//
//  Created by Romain GUICHERD on 25/01/2020.
//  Copyright © 2020 Romain GUICHERD. All rights reserved.
//

#ifndef game_h
#define game_h


void game(SDL_Window* window);
void movePlayer(int map[][NB_BLOCKS_HEIGHT], SDL_Rect *pos, int direction);
void moveCrate(int *firstBlock, int *secondBlock);

#endif /* game_h */
