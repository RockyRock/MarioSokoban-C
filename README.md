# Mario Sokoban

This repository contains a Mario sokoban game coded in C from the tutorial provided by [Open Classrooms](https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/18709-tp-mario-sokoban). This game has been created with Xcode using the [SDL2](https://www.libsdl.org/index.php) and [SDL2 Image](https://www.libsdl.org/projects/SDL_image/) libraries.

## Game

The main goal of this game is to position all the crate on the objectives using Mario. The objectives are represented by green dots, the crate turn red once they are placed on an objective. Mario can only push one crate at a time and is controlled using the keyboard arrows.

## Editor

This game includes an editor taht allows to change the position of the elements of the map. In editor mode the keys are used as follows:

- `1` select a wall element
- '2' select a crate elemet
- `3` select an objective element
- `4` select Mario
- `5` select a crate on an objective
- `s` save the current game map
- `esc` go back to the main menu
- `left click` position the element selected at the cursor location
- `right click` remove the element under at the cursor location
