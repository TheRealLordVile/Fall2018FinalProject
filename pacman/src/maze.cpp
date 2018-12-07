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
    layout  =
    {{WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
    {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
    {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
    {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
    {WALL,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
    {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
    {WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,COIN,WALL},
    {WALL,COIN,COIN,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,WALL,WALL,COIN,COIN,COIN,COIN,COIN,COIN,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
{WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},     {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
{WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},        {WALL,WALL,WALL,WALL,WALL,WALL,COIN,WALL,WALL,EMPTY,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,EMPTY,WALL,WALL,COIN,WALL,WALL,WALL,WALL,WALL,WALL},
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
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}};
    init_num_coins = 0;
    for (std::vector<mazeElement> row:layout) {
        for (mazeElement e : row) {
            if (e == COIN) {
                init_num_coins++;
            }
        }
    }
    
    current_num_coins = init_num_coins;
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

std::pair<int,int> Maze::canPacmanMove (int pacman_direction, std::pair<int,int> pos) {
    int x = pos.first;
    int y = pos.second;
    switch (pacman_direction) {
        case 1:
            if (x == 0) {
                return pos;
            }
            
            if (layout[x-1][y] != WALL) {
                checkCollision(x-1,y);
                layout[x][y] = EMPTY;
                layout[x-1][y] = PACMAN;
                return std::make_pair(x-1, y);
            }
            break;
        case 2:
            if (x == layout[0].size()+1) {
                return pos;
            }
            
            if (layout[x+1][y] != WALL) {
                checkCollision(x+1,y);
                layout[x][y] = EMPTY;
                layout[x+1][y] = PACMAN;
                return std::make_pair(x+1,y);
            }
            
            break;
        case 3:
            if(x == 14 && y == 0){
                layout[x][y] = EMPTY;
                layout[x][layout[0].size()-1] = PACMAN;
                return std::make_pair(x, layout[0].size()-1);
            }
            if (layout[x][y-1] != WALL) {
                checkCollision(x,y-1);
                layout[x][y] = EMPTY;
                layout[x][y-1] = PACMAN;
                return std::make_pair(x,y-1);
            }
    
            break;
        case 4:
            if(x == 14 && y == layout[0].size()-1) {
                layout[x][y] = EMPTY;
                layout[x][0] = PACMAN;
                return std::make_pair(x,0);
            }
            
            if (layout[x][y+1] != WALL) {
                checkCollision(x,y+1);
                layout[x][y] = EMPTY;
                layout[x][y+1] = PACMAN;
                return std::make_pair(x,y+1);
            }
    }
    
    return pos;
}

void Maze::checkCollision(int x, int y) {
    mazeElement element = layout[x][y];
    switch (element) {
        case EMPTY:
            break;
        case COIN:
            current_num_coins--;
            break;
    }
}

int Maze::getNumberOfCoins() {
    return init_num_coins - current_num_coins;
}
