//
//  ghost.hpp
//  pacman
//
//  Created by A.Kadri Türker on 12/8/18.
//

#ifndef ghost_hpp
#define ghost_hpp
#include <stdio.h>
#include <ofMain.h>
class Ghost {
public:
    Ghost(int type);
    std::pair<int,int> pos;
    
    enum ghostDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    ofImage getGhostSprite();
    ghostDirection getDirection();
    void setDirection(ghostDirection new_direct);
private:
    ofImage ghost_sprite;
    ghostDirection direction;
};
#endif /* ghost_hpp */
