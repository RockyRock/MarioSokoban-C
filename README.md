# Mario Sokoban

This repository contains a Mario sokoban game coded in C from the tutorial provided by [Open Classrooms](https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/18709-tp-mario-sokoban). This game has been created with Xcode using the [SDL2](https://www.libsdl.org/index.php) and [SDL2 Image](https://www.libsdl.org/projects/SDL_image/) libraries.

## Game

The main goal of this game is to position all the crates on the objectives using Mario. The objectives are represented by green dots, such that,

![Objective](/Mario_Sokoban/sprites_mario_sokoban/objectif.png)

A crate is represented by the following element,

![Crate](/Mario_Sokoban/sprites_mario_sokoban/caisse.jpg)

A crate will turn red once placed on an objective such that,

![CrateOK](/Mario_Sokoban/sprites_mario_sokoban/caisse_ok.jpg)

The map is limited by walls represented by

![Wall](/Mario_Sokoban/sprites_mario_sokoban/mur.jpg)

Mario can only push one crate at a time and is controlled via the keyboard arrows. Pressing escape will return to the game menu.

## Editor

This game includes an editor that allows to change the position of the elements on the map. In editor mode, the keys of the keyboard are used as follows:

- `1` select a wall element
- `2` select a crate elemet
- `3` select an objective element
- `4` select Mario
- `5` select a crate on an objective
- `s` save the current game map
- `esc` go back to the main menu
- `left click` position the element selected at the cursor location
- `right click` remove the element at the cursor location
