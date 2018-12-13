//
//  ghost.cpp
//  pacman
//
//  Created by A.Kadri Türker on 12/8/18.
//

#include "ghost.hpp"
Ghost::Ghost(int ghost_type) {
    std::string img_path;
    // The corresponding image is set as the sprite according to the ghost type.
    switch (ghost_type) {
        case 1:
            img_path = kGhost1ImgPath;
            break;
        case 2:
            img_path = kGhost2ImgPath;
            break;
        case 3:
            img_path = kGhost3ImgPath;
            break;
        case 4:
            img_path = kGhost4ImgPath;
            break;
        case 5:
            img_path = kGhost5ImgPath;
    }

    ghost_sprite.load(img_path);
    // The inital direction of each ghost is LEFT.
    direction = LEFT;
}

ofImage Ghost::getGhostSprite() {
    return ghost_sprite;
}

void Ghost::setDirection(int new_direct) {
    // Given int value is cast into a ghost direction enum.
    direction = (ghostDirection)new_direct;
}

Ghost::ghostDirection Ghost::getDirection() {
    return direction;
}

std::pair<int,int> Ghost::getPos() {
    return pos;
}

void Ghost::setPos(std::pair<int,int> new_pos) {
    pos = new_pos;
}
