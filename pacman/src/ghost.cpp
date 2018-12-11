//
//  ghost.cpp
//  pacman
//
//  Created by A.Kadri Türker on 12/8/18.
//

#include "ghost.hpp"
Ghost::Ghost(int type) {
    std::string img_path;
    switch (type) {
        case 1:
            img_path = "../../images/ghost_1.png";
            break;
        case 2:
            img_path = "../../images/ghost_2.png";
            break;
        case 3:
            img_path = "../../images/ghost_3.png";
            break;
        case 4:
            img_path = "../../images/ghost_4.png";
            break;
        case 5:
            img_path = "../../images/ghost_5.png";
    }

    ghost_sprite.load(img_path);
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
