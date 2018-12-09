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
            break;
        case 2:
            ghost_sprite.load("../../images/ghost_2.png");
            break;
        case 3:
            ghost_sprite.load("../../images/ghost_3.png");
            break;
    }
    
    direction = LEFT;
}

ofImage Ghost::getGhostSprite() {
    return ghost_sprite;
}

void Ghost::setDirection(int new_direct) {
    direction = (ghostDirection)new_direct;
}

Ghost::ghostDirection Ghost::getDirection() {
    return direction;
}
