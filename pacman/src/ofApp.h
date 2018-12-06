#pragma once

#include "ofMain.h"
#include "maze.hpp"
#include "pacman.hpp"

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
    ofSoundPlayer pacmanSiren;
    ofSoundPlayer wakaWaka;
    Maze maze;
    Pacman pacman;
    void setUpSounds();
    void updatePacman();
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
