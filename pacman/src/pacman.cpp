//
//  pacman.cpp
//  pacman
//
//  Created by A.Kadri Türker on 11/18/18.
//

#include "pacman.hpp"

Pacman::Pacman() {
    num_lives = kInitNumLives;
    anim_count = kInitAnimCount;
    pacman_sprite_0.load(kSprite0ImgPath);
    pacman_sprite_1.load(kSprite1ImgPath);
    pacman_sprite_2.load(kSprite2ImgPath);
    direction_moving = RIGHT;
}

ofImage Pacman::getPacmanSprite() {
    ofImage to_be_returned;
    
    switch (anim_count) {
        case 0:
            to_be_returned = pacman_sprite_0;
            anim_count++;
            break;
        case 1:
            to_be_returned = pacman_sprite_1;
            anim_count++;
            break;
        case 2:
            to_be_returned = pacman_sprite_2;
            anim_count = kInitAnimCount;
            break;
    }
    
    switch (direction_moving) {
        case NONE:
            to_be_returned = pacman_sprite_1;
            to_be_returned.rotate90(last_rotation);
            break;
        case UP:
            last_rotation = kUpRotationAmount;
            to_be_returned.rotate90(kUpRotationAmount);
            break;
        case DOWN:
            last_rotation = kDownRotationAmount;
            to_be_returned.rotate90(kDownRotationAmount);
            break;
        case LEFT:
            last_rotation = kLeftRotationAmount;
            to_be_returned.rotate90(kLeftRotationAmount);
            break;
        case RIGHT:
            last_rotation = kRightRotationAmount;
    }
    
    return to_be_returned;
}

Pacman::Direction Pacman::getDirection() {
    return direction_moving;
}
void Pacman::setDirection(Pacman::Direction new_dir) {
    direction_moving = new_dir;
}

std::pair<int,int> Pacman::getPos() {
    return pos;
}

void Pacman::setPos(std::pair<int,int> new_pos) {
    pos = new_pos;
}

int Pacman::getNumLives() {
    return num_lives;
}
void Pacman::setNumLives(int new_num_lives) {
    num_lives = new_num_lives;
}
