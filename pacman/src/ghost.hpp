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
    // Enums to represent possible directoin, different from pacman since ghosts
    // can't stop.
    enum ghostDirection {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };
    
    // Constructor of the class takes in the type of the ghost as the only
    // parameter.
    Ghost(int ghost_type);

    ofImage getGhostSprite();
    ghostDirection getDirection();
    
    // Necessary setters and getters for class variables.
    void setDirection(int new_direct);
    std::pair<int,int> getPos();
    void setPos(std::pair<int,int> new_pos);

private:
    // Constants.
    // Cannot use the word const to be able to use the copy assignment operator.
    std::string kGhost1ImgPath = "../../images/ghost_1.png";
    std::string kGhost2ImgPath = "../../images/ghost_2.png";
    std::string kGhost3ImgPath = "../../images/ghost_3.png";
    std::string kGhost4ImgPath = "../../images/ghost_4.png";
    std::string kGhost5ImgPath = "../../images/ghost_5.png";

    // Class variables.
    ofImage ghost_sprite;
    ghostDirection direction;
    std::pair<int,int> pos;
};
#endif /* ghost_hpp */
