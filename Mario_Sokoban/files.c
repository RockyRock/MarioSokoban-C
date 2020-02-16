//
//  files.c
//  File management to save and load game files
//  Mario_Sokoban
//
//  Created by Romain GUICHERD on 25/01/2020.
//  Copyright © 2020 Romain GUICHERD. All rights reserved.
//

#include <stdio.h>

#include "constants.h"
#include "files.h"

int loadLevel(int map[][NB_BLOCKS_HEIGHT]){
    
    // Initialization
    FILE* file = NULL;
    char lineFile[NB_BLOCKS_WIDTH * NB_BLOCKS_WIDTH + 1] = {0};
    int i = 0, j = 0;

    // Open file level.lvl in read mode and check
    file = fopen("level.lvl", "r");
    if (file == NULL){
        fprintf(stderr, "Cannot open file level.lvl\n");
        return 0;
    }
    
    // Read file
    fgets(lineFile, NB_BLOCKS_WIDTH * NB_BLOCKS_HEIGHT + 1, file);
    
    // Test on line file
    for (i = 0; i < NB_BLOCKS_WIDTH; i++){
        for (j = 0; j < NB_BLOCKS_HEIGHT; j++){
            switch (lineFile[(i * NB_BLOCKS_WIDTH) + j]){
                case '0':
                    map[j][i] = 0;
                    break;
                case '1':
                    map[j][i] = 1;
                    break;
                case '2':
                    map[j][i] = 2;
                    break;
                case '3':
                    map[j][i] = 3;
                    break;
                case '4':
                    map[j][i] = 4;
                    break;
                case '5':
                    map[j][i] = 5;
                    break;
            }
        }
    }
    
    // Close file and return
    fclose(file);
    return 1;
}

int saveLevel(int map[][NB_BLOCKS_HEIGHT]){
    
    // Initialization
    FILE* file = NULL;
    int i = 0, j = 0;

    // Open file in write mode and check
    file = fopen("level.lvl", "w");
    if (file == NULL){
        fprintf(stderr, "Cannot open file level.lvl\n");
        return 0;
    }

    // Write in file
    for (i = 0 ; i < NB_BLOCKS_WIDTH; i++){
        for (j = 0; j < NB_BLOCKS_HEIGHT; j++){
            fprintf(file, "%d", map[j][i]);
        }
    }

    // Close file and return
    fclose(file);
    return 1;
}
