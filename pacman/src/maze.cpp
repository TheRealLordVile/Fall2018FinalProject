//
//  maze.cpp
//  pacman
//
//  Created by A.Kadri Türker on 11/11/18.
//

#include "maze.hpp"
Maze::Maze(){
    background.load("../../images/background.png");
    coin_sprite.load("../../images/coin.png");
    pacman_x = 17;
    pacman_y = 14;
    layout  =
    {{WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN, WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,COIN,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,COIN,EMPTY,EMPTY,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,EMPTY,EMPTY,COIN,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,PACMAN,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
        {WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,WALL},
        {WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL},
        {WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL},
        {WALL,COIN,COIN,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL},
        {WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
        {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}
    };
}

void Maze::updateLayout(int col, int row, mazeElement new_value) {
    layout[col][row] = new_value;
}

ofImage Maze::getCoinSprite() {
    return coin_sprite;
}

Maze::mazeElement Maze::getElementAt(int col, int row) {
    return layout[col][row];
}

int Maze::getMazeHeight() {
    return layout.size();
}

int Maze::getMazeWidth() {
    return layout[0].size();
}
ofImage Maze::getBackground() {
    return background;
}

bool Maze::canPacmanMove(int pacman_direction) {
    switch (pacman_direction) {
        case 1:
            if (pacman_x == 0) {
                return false;
            }
            
            if (layout[pacman_x-1][pacman_y] != WALL) {
                layout[pacman_x][pacman_y] = EMPTY;
                layout[pacman_x-1][pacman_y] = PACMAN;
                return true;
            }
            break;
        case 2:
            if (pacman_x == layout[0].size()-1) {
                return false;
            }
            
            if (layout[pacman_x+1][pacman_y] != WALL) {
                layout[pacman_x][pacman_y] = EMPTY;
                layout[pacman_x+1][pacman_y] = PACMAN;
                return true;
            }
            
            break;
        case 3:
            if (pacman_y == 0) {
                return false;
            }
            
            if (layout[pacman_x][pacman_y-1] != WALL) {
                layout[pacman_x][pacman_y] = EMPTY;
                layout[pacman_x][pacman_y-1] = PACMAN;
                return true;
            }
    
            break;
        case 4:
            if (pacman_y == layout.size()-1) {
                return false;
            }
            
            if (layout[pacman_x][pacman_y+1] != WALL) {
                layout[pacman_x][pacman_y] = EMPTY;
                layout[pacman_x][pacman_y+1] = PACMAN;
                return true;
            }
    }
    
    return false;
}
