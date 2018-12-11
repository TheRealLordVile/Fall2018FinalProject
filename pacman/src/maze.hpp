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
#include <nlohmann/json.hpp>
class Maze {
public:
    enum mazeElement{
        EMPTY = 0,
        WALL = 1,
        COIN = 2,
        PACMAN = 3,
        GHOST1 = 4,
        GHOST2 = 5,
        GHOST3 = 6,
        GHOST4 = 7,
        GHOST5 = 8
    };
    
    Maze(int level_num);
    void updateLayout(int col, int row, mazeElement new_value);
    ofImage getCoinSprite();
    ofImage getBackground();
    mazeElement getElementAt(int col, int row);
    int getMazeHeight();
    int getMazeWidth();
    std::pair<int,int>getInitPacmanPosition();
    std::pair<int,int>getInitGhostPosition(int ghost_type);

    std::pair<int,int> canPacmanMove(int pacman_direction, std::pair<int,int> pos);
    std::pair<int,int> canGhostMove(int ghost_type, int ghost_direction, std::pair<int,int> pos);
    int getNumberOfCoins();
    bool areAllCoinsEaten();
    bool isPacmanAlive();
private:
    void setUpLayout(int num_level);
    void setUpNumCoins();
    bool pacman_alive;
    void checkCollision(int x, int y);
    int init_num_coins;
    int current_num_coins;
    ofImage background;
    ofImage coin_sprite;
    std::vector<std::vector<mazeElement>> layout;

};





#endif /* maze_hpp */
