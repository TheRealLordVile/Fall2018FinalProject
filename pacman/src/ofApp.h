#pragma once

#include "ofMain.h"
#include "maze.hpp"
#include <cstdlib>
#include "pacman.hpp"
#include "ghost.hpp"

class pacmanGame : public ofBaseApp{
    enum GameState {
        START_SCREEN,
        IN_PROGRESS,
        PAUSED,
        LEADERBOARD,
        ENDING_SCREEN
    };
    
    GameState current_state;
    ofRectangle start_var;
    ofRectangle leaderboard_var;
    int level_num;
    std::vector<int> leaderboard;
    
    ofSoundPlayer start_song;
    ofSoundPlayer pacman_siren;
    ofSoundPlayer waka_waka;
    ofSoundPlayer pacman_dying;
    ofSoundPlayer paused_sound;
    ofSoundPlayer ending_song;
    Maze maze{1};
    Pacman pacman;
    
    Ghost ghost_1{1};
    Ghost ghost_2{2};
    Ghost ghost_3{3};
    Ghost ghost_4{4};
    Ghost ghost_5{5};

    void setUpSounds();
    void setUpPositions();
    void setUpLeaderboardValues();
    void updatePacman();
    void updateGhosts();
    void updateGhost1();
    void updateGhost2();
    void updateGhost3();
    void updateGhost4();
    void updateGhost5();
    void updateLeaderboard();
    void loadNewLevel();


    void drawStartScreen();
    void drawPauseScreen();
    void drawGameState();
    void drawLeaderboard();
    void drawEndingScreen();
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
