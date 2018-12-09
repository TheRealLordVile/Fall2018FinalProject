#pragma once

#include "ofMain.h"
#include "maze.hpp"
#include <cstdlib>
#include "pacman.hpp"
#include "ghost.hpp"

class pacmanGame : public ofBaseApp{
    std::pair<double,double> start_coord_x;
    std::pair<double,double> start_coord_y;

    std::pair<double,double> leader_coord_x;
    std::pair<double,double> leader_coord_y;
    enum GameState {
        START_SCREEN,
        IN_PROGRESS,
        PAUSED,
        FINISHED
    };
    
    GameState current_state = START_SCREEN;
    ofSoundPlayer start_song;
    ofSoundPlayer pacman_siren;
    ofSoundPlayer waka_waka;
    Maze maze;
    Pacman pacman;
    Ghost ghost_1{1};
    Ghost ghost_2{2};
    Ghost ghost_3{3};

    void setUpSounds();
    void updatePacman();
    void updateGhosts();
    void updateGhost1();
    void updateGhost2();
    void updateGhost3();

    void drawStartScreen();
    void drawPauseScreen();
    void drawGameState();
    void adjustPacmanSound();
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
};
