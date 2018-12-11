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
    Ghost(int ghost_type);
    std::pair<int,int> pos;
    
    enum ghostDirection {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };
    
    ofImage getGhostSprite();
    ghostDirection getDirection();
    void setDirection(int new_direct);
private:
    std::string kGhost1ImgPath = "../../images/ghost_1.png";
    std::string kGhost2ImgPath = "../../images/ghost_2.png";
    std::string kGhost3ImgPath = "../../images/ghost_3.png";
    std::string kGhost4ImgPath = "../../images/ghost_4.png";
    std::string kGhost5ImgPath = "../../images/ghost_5.png";

    ofImage ghost_sprite;
    ghostDirection direction;
};
#endif /* ghost_hpp */
