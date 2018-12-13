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
    
    // Enums for the direction, pacman can not move as well.
    enum Direction {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    
    Pacman();
    
    // Getters and Setters.
    ofImage getPacmanSprite();
    Direction getDirection();
    void setDirection(Direction new_dir);
    std::pair<int,int> getPos();
    void setPos(std::pair<int,int> new_pos);
    int getNumLives();
    void setNumLives(int new_num_lives);
    
private:
    // Constants
    // Cannot use the word const to be able to use the copy assignment operator.
    int kInitNumLives = 3;
    int kInitAnimCount = 0;
    int kMaxAnimCount = 2;
    int kUpRotationAmount = 3;
    int kDownRotationAmount = 1;
    int kLeftRotationAmount = 2;
    int kRightRotationAmount = 0;
    std::string kSprite0ImgPath = "../../images/pacman_0.png";
    std::string kSprite1ImgPath = "../../images/pacman_1.png";
    std::string kSprite2ImgPath = "../../images/pacman_2.png";

    // Class variables.
    std::pair<int,int> pos;
    int num_lives;
    int anim_count;
    int last_rotation;
    Direction direction_moving;
    ofImage pacman_sprite_0;
    ofImage pacman_sprite_1;
    ofImage pacman_sprite_2;
};
#endif /* pacman_hpp */
