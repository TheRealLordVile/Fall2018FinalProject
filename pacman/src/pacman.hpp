//
//  pacman.hpp
//  pacman
//
//  Created by A.Kadri Türker on 11/18/18.
//

#ifndef pacman_hpp
#define pacman_hpp

#include <stdio.h>
#include <ofMain.h>

class Pacman {
public:
    std::pair<int,int> pos;
    enum Direction {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    
    Pacman();
    ofImage getPacmanSprite();
    void increasePoints(int increase_amount);
    int getNumberOfPoints();
    Direction getDirection();
    void updatePos();
    void setDirection(Direction new_dir);
private:
    Direction direction_moving;
    int num_points;
    int anim_count;
    int num_lives;
    ofImage pacman_sprite_1;
    ofImage pacman_sprite_2;
    ofImage pacman_sprite_3;
};
#endif /* pacman_hpp */
