//
//  maze.hpp
//  pacman
//
//  Created by A.Kadri Türker on 11/11/18.
//

#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <ofMain.h>
#include <stdio.h>
#include <nlohmann/json.hpp>

class Maze {
public:
    // Enums for different elements in the maze.
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
    
    // The cosntructor takes in the current level number as the only parameter.
    Maze(int level_num);
    ofImage getCoinSprite();
    ofImage getBackground();
    
    // Returns the element at the specified location on the layout.
    mazeElement getElementAt(int col, int row);
    
    // Returns the length or width of the layout.
    int getMazeHeight();
    int getMazeWidth();
    
    //Finds the position of the element in the layout and returns it.
    std::pair<int,int>getInitPacmanPosition();
    std::pair<int,int>getInitGhostPosition(int ghost_type);
    
    // The can move methods check the direction and current position to find a
    // position they update the pacman_alive abd current_num_coins variables.
    std::pair<int,int> canPacmanMove(int pacman_direction,
                                     std::pair<int,int> pos);
    std::pair<int,int> canGhostMove(int ghost_type, int ghost_direction,
                                    std::pair<int,int> pos);
    // Returns the number of coins.
    int getNumberOfCoins();
    
    // Returns a boolean value that represents if all the coins are eaten.
    bool areAllCoinsEaten();
    
    // Returns a boolean value that represents if pacman is alive.
    bool isPacmanAlive();
private:
    // The constants, arrenged by their type.
    // Couldn't use const on objects that are constants.
    std::string kLayoutImgPath = "../../images/background.png";
    std::string kCoinImgPath = "../../images/coin.png";
    std::string kLevel1LayoutPath = "layout_level_1.json";
    std::string kLevel2LayoutPath = "layout_level_2.json";
    std::string kLevel3LayoutPath = "layout_level_3.json";
    std::string kLevel4AndMoreLayoutPath = "layout_level_4+.json";
    std::pair<int,int> kInitialPacmanPos = std::make_pair(17,14);
    static const int kPacmanUp = 1;
    static const int kPacmanDown = 2;
    static const int kPacmanLeft = 3;
    static const int kPacmanRight = 4;
    static const int kGhostUp = 0;
    static const int kGhostDown = 1;
    static const int kGhostLeft = 2;
    static const int kGhostRight = 3;
    
    // Class variables
    bool pacman_alive;
    // Two variables to keep track of the inital and current number of coins.
    int init_num_coins;
    int current_num_coins;
    ofImage background;
    ofImage coin_sprite;
    // A 2d vector that represents the maze layout.
    std::vector<std::vector<mazeElement>> layout;
    
    // Imports the layout from a json file according to the number of the level.
    void setUpLayout(int num_level);
    
    // Couns the number of coins in the cureent level and initializes
    // the corresponding variables.
    void setUpNumCoins();
    
    // Checks collisions for pacmans movements.
    void checkCollision(int x, int y);

    

};

#endif /* maze_hpp */
