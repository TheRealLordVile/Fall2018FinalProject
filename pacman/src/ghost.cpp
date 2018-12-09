//
//  ghost.cpp
//  pacman
//
//  Created by A.Kadri Türker on 12/8/18.
//

#include "ghost.hpp"
Ghost::Ghost(int type) {
    
    switch (type) {
        case 1:
            ghost_sprite.load("../../images/ghost_1.png");
            direction = LEFT;
            break;
        case 2:
            ghost_sprite.load("../../images/ghost_2.png");
            direction = RIGHT;
            break;
        case 3:
            ghost_sprite.load("../../images/ghost_3.png");
            direction = UP;
            break;
    }
}

ofImage Ghost::getGhostSprite() {
    return ghost_sprite;
}

void Ghost::setDirection(ghostDirection new_direct) {
    direction = new_direct;
}

Ghost::ghostDirection Ghost::getDirection() {
    return direction;
}
