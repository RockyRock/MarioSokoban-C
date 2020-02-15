//
//  constants.h
//  Definition of the game constants
//  Mario_Sokoban
//
//  Created by Romain GUICHERD on 25/01/2020.
//  Copyright © 2020 Romain GUICHERD. All rights reserved.
//

#ifndef constants_h
#define constants_h


#define SIZE_BLOCK          34 // Block size (square) in pixels
#define NB_BLOCKS_WIDTH     12
#define NB_BLOCKS_HEIGHT    12
#define WIDTH_WINDOW        SIZE_BLOCK * NB_BLOCKS_WIDTH
#define HEIGHT_WINDOW       SIZE_BLOCK * NB_BLOCKS_HEIGHT

enum {UP, DOWN, LEFT, RIGHT};
enum {VOID, WALL, CRATE, OBJECTIVE, MARIO, CRATE_OK};

#endif /* constants_h */
