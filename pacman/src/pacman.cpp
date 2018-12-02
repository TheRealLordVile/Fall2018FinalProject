//
//  pacman.cpp
//  pacman
//
//  Created by A.Kadri Türker on 11/18/18.
//

#include "pacman.hpp"

Pacman::Pacman() {
    num_lives = 3;
    num_points = 0;
    anim_count = 0;
    pacman_sprite_1.load("../../images/pacman_1.png");
    pacman_sprite_2.load("../../images/pacman_1.png");
    pacman_sprite_3.load("../../images/pacman_1.png");
    direction_moving = NONE;
}

ofImage Pacman::getPacmanSprite() {
    ofImage to_be_returned = pacman_sprite_1;
    
    switch (anim_count) {
        case 1:
            to_be_returned = pacman_sprite_2;
            break;
        case 2:
            to_be_returned = pacman_sprite_3;
            break;
    }
    if (anim_count == 2) {
        anim_count = 0;
    
    } else{
        anim_count++;
    }
    
    return to_be_returned;
}

void Pacman::increasePoints(int increase_amount){
    num_points += increase_amount;
}

int Pacman::getNumberOfPoints() {
    return num_points;
    
}
Pacman::Direction Pacman::getDirection() {
    return direction_moving;
}
void Pacman::setDirection(Pacman::Direction new_dir) {
    direction_moving = new_dir;
}



