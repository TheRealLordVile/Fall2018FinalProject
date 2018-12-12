//
//  maze.cpp
//  pacman
//
//  Created by A.Kadri Türker on 11/11/18.
//

#include "maze.hpp"
Maze::Maze(int num_level) {
    background.load(kLayoutImgPath);
    coin_sprite.load(kCoinImgPath);
    setUpLayout(num_level);
    setUpNumCoins();
    pacman_alive = true;
}

void Maze::setUpLayout(int num_level) {
    ofFile layout_file;
    std::string data_path;
    
    switch (num_level) {
        case 4 ... INT_MAX:
            data_path = kLevel4MoreImgPath;
            break;
        case 3:
            data_path = kLevel3ImgPath;
            break;
        case 2:
            data_path = kLevel2ImgPath;
            break;
        case 1:
            data_path = kLevel1ImgPath;
            break;
    }
    
    layout_file.open(ofToDataPath(data_path), ofFile::ReadWrite, true);
    nlohmann::json json;
    json << layout_file;
    layout_file.close();
    
    std::vector<std::vector<int>> int_layout =
    json.get<std::vector<std::vector<int>>>();
    
    layout = std::vector<std::vector<mazeElement>>();
    for(std::vector<int> int_row: int_layout) {
        std::vector<mazeElement> row;
        for (int element: int_row) {
            row.push_back((mazeElement)element);
        }
        layout.push_back(row);
    }
}

void Maze::setUpNumCoins() {
    // Set to 0 for initialization.
    init_num_coins = 0;
    for (std::vector<mazeElement> row:layout) {
        for (mazeElement e : row) {
            if (e == COIN) {
                init_num_coins++;
            }
        }
    }
    
    current_num_coins = init_num_coins;
}

void Maze::updateLayout(int col, int row, mazeElement new_value) {
    layout[col][row] = new_value;
}

std::pair<int,int> Maze::getInitPacmanPosition() {
    for (int x = 0; x < layout.size(); x++) {
        for (int y = 0; y < layout[0].size(); y++) {
            if (layout[x][y] == PACMAN) {
                return std::make_pair(x, y);
                
            }
        }
    }
}

std::pair<int,int> Maze::getInitGhostPosition(int ghost_type) {
    mazeElement ghost;
    
    switch (ghost_type) {
        case 1:
            ghost = GHOST1;
            break;
        case 2:
            ghost = GHOST2;
            break;
        case 3:
            ghost = GHOST3;
            break;
        case 4:
            ghost = GHOST4;
            break;
        case 5:
            ghost = GHOST5;
    }
    
    for (int x = 0; x<layout.size(); x++) {
        for (int y = 0; y<layout[0].size(); y++) {
            if (layout[x][y] == ghost) {
                return std::make_pair(x, y);
                
            }
        }
    }
    return std::make_pair(0, 0);
}


ofImage Maze::getCoinSprite() {
    return coin_sprite;
}

Maze::mazeElement Maze::getElementAt(int col, int row) {
    return layout[col][row];
}

int Maze::getMazeHeight() {
    return layout.size();
}

int Maze::getMazeWidth() {
    return layout[0].size();
}
ofImage Maze::getBackground() {
    return background;
}

std::pair<int,int> Maze::canPacmanMove (int pacman_direction, std::pair<int,int> pos) {
    int x = pos.first;
    int y = pos.second;
    
    if (!pacman_alive) {
        layout[x][y] = EMPTY;
        layout[kInitialPacmanPos.first][kInitialPacmanPos.second] = PACMAN;
        return kInitialPacmanPos;
    }
    
    switch (pacman_direction) {
        case kPacmanUp:
            if (x == 0) {
                return pos;
            }
            
            if (layout[x-1][y] != WALL) {
                checkCollision(x-1,y);
                if (!pacman_alive) {
                    layout[x][y] = EMPTY;
                    layout[kInitialPacmanPos.first][kInitialPacmanPos.second]
                    = PACMAN;
                    return kInitialPacmanPos;
                }
                layout[x][y] = EMPTY;
                layout[x-1][y] = PACMAN;
                return std::make_pair(x-1, y);
            }
            break;
        case kPacmanDown:
            if (x == layout[0].size()+1) {
                return pos;
            }
            
            if (layout[x+1][y] != WALL) {
                checkCollision(x+1,y);
                if (!pacman_alive) {
                    layout[x][y] = EMPTY;
                    layout[kInitialPacmanPos.first][kInitialPacmanPos.second]
                    = PACMAN;
                    return kInitialPacmanPos;
                }
                layout[x][y] = EMPTY;
                layout[x+1][y] = PACMAN;
                return std::make_pair(x+1,y);
            }
            
            break;
        case kPacmanLeft:
            if(x == kInitialPacmanPos.second && y == 0){
                layout[x][y] = EMPTY;
                layout[x][layout[0].size()-1] = PACMAN;
                return std::make_pair(x, layout[0].size()-1);
            }
            if (layout[x][y-1] != WALL) {
                checkCollision(x,y-1);
                if (!pacman_alive) {
                    layout[x][y] = EMPTY;
                    layout[kInitialPacmanPos.first][kInitialPacmanPos.second]
                    = PACMAN;
                    return kInitialPacmanPos;
                }
                layout[x][y] = EMPTY;
                layout[x][y-1] = PACMAN;
                return std::make_pair(x,y-1);
            }
    
            break;
        case kPacmanRight:
            if(x == kInitialPacmanPos.second && y == layout[0].size()-1) {
                layout[x][y] = EMPTY;
                layout[x][0] = PACMAN;
                return std::make_pair(x,0);
            }
            
            if (layout[x][y+1] != WALL) {
                checkCollision(x,y+1);
                if (!pacman_alive) {
                    layout[x][y] = EMPTY;
                    layout[kInitialPacmanPos.first][kInitialPacmanPos.second]
                    = PACMAN;
                    return kInitialPacmanPos;
                }
                layout[x][y] = EMPTY;
                layout[x][y+1] = PACMAN;
                return std::make_pair(x,y+1);
            }
    }
    
    return pos;
}

void Maze::checkCollision(int x, int y) {
    mazeElement element = layout[x][y];
    switch (element) {
        case EMPTY:
            break;
        case COIN:
            current_num_coins--;
            break;
        case GHOST1:
        case GHOST2:
        case GHOST3:
        case GHOST4:
        case GHOST5:
            pacman_alive = false;
    }
}

int Maze::getNumberOfCoins() {
    return init_num_coins - current_num_coins;
}

bool Maze::areAllCoinsEaten() {
    return current_num_coins == 0;
}

bool Maze::isPacmanAlive() {
    if (!pacman_alive) {
        pacman_alive = true;
        return false;
    }
    
    return true;
}

std::pair<int,int> Maze::canGhostMove (int ghost_type, int ghost_direction,
                                       std::pair<int,int> pos) {
    mazeElement ghost;
    switch (ghost_type) {
        case 1:
            ghost = GHOST1;
            break;
        case 2:
            ghost = GHOST2;
            break;
        case 3:
            ghost = GHOST3;
            break;
        case 4:
            ghost = GHOST4;
            break;
        case 5:
            ghost = GHOST5;
    }
    
    int x = pos.first;
    int y = pos.second;
    bool ghosts_collide;
    switch (ghost_direction) {
        case kGhostUp:
            ghosts_collide = layout[x-1][y] == GHOST1 ||
                             layout[x-1][y] == GHOST2 ||
                             layout[x-1][y] == GHOST3 ||
                             layout[x-1][y] == GHOST4 ||
                             layout[x-1][y] == GHOST5;
            if (x == 0 || ghosts_collide) {
                return pos;
            }
            
            if (layout[x-1][y] != WALL) {
                if (layout[x-1][y] == PACMAN){
                    pacman_alive = false;
                    layout[x][y] = EMPTY;
                } else {
                    layout[x][y] = layout[x-1][y];
                }
                
                layout[x-1][y] = ghost;
                return std::make_pair(x-1, y);
            }
            
            break;
            
        case kGhostDown:
            ghosts_collide = layout[x+1][y] == GHOST1 ||
                             layout[x+1][y] == GHOST2 ||
                             layout[x+1][y] == GHOST3 ||
                             layout[x+1][y] == GHOST4 ||
                             layout[x+1][y] == GHOST5;
            
            if (x >= layout.size() - 2 || ghosts_collide) {
                return pos;
            }
            
            if (layout[x+1][y] != WALL) {
                if (layout[x+1][y] == PACMAN){
                    pacman_alive = false;
                    layout[x][y] = EMPTY;
                } else {
                    layout[x][y] = layout[x+1][y];
                }
                layout[x+1][y] = ghost;
                return std::make_pair(x+1,y);
            }
            
            break;
        case kGhostLeft:
            ghosts_collide = layout[x][y-1] == GHOST1 ||
                             layout[x][y-1] == GHOST2 ||
                             layout[x][y-1] == GHOST3 ||
                             layout[x][y-1] == GHOST4 ||
                             layout[x][y-1] == GHOST5;

            if (y == 0 || ghosts_collide) {
                return pos;
            }
            
            if (layout[x][y-1] != WALL) {
                if (layout[x][y-1] == PACMAN){
                    pacman_alive = false;
                    layout[x][y] = EMPTY;
                } else {
                    layout[x][y] = layout[x][y-1];
                }
                layout[x][y-1] = ghost;
                return std::make_pair(x,y-1);
            }
            
            break;
        case kGhostRight:
            ghosts_collide = layout[x][y+1] == GHOST1 ||
                             layout[x][y+1] == GHOST2 ||
                             layout[x][y+1] == GHOST3 ||
                             layout[x][y+1] == GHOST4 ||
                             layout[x][y+1] == GHOST5;
            if (y == layout[0].size() - 2 || ghosts_collide) {
                return pos;
            }
            
            if (layout[x][y+1] != WALL) {
                if (layout[x][y+1] == PACMAN){
                    pacman_alive = false;
                    layout[x][y] = EMPTY;
                } else {
                    layout[x][y] = layout[x][y+1];
                }
                
                layout[x][y+1] = ghost;
                return std::make_pair(x,y+1);
            }
    }
    
    return pos;
}
