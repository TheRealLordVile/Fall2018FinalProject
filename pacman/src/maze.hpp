//
//  maze.hpp
//  pacman
//
//  Created by A.Kadri Türker on 11/11/18.
//

#ifndef MAZE_HPP
#define MAZE_HPP

#include <stdio.h>
#include <vector>
#include <ofMain.h>

class Maze {
public:
    enum mazeElement{
        EMPTY = 0,
        WALL = 1,
        COIN = 2,
        PACMAN = 3
    };
    Maze();
    void updateLayout(int col, int row, mazeElement new_value);
    ofImage getCoinSprite();
    ofImage getBackground();
    mazeElement getElementAt(int col, int row);
    int getMazeHeight();
    int getMazeWidth();
    bool canPacmanMove(int pacman_direction);
private:
    int pacman_x;
    int pacman_y;
    ofImage background;
    ofImage coin_sprite;
    std::vector<std::vector<mazeElement>> layout;

};





#endif /* maze_hpp */
