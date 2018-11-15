#pragma once

#include "ofMain.h"
#include "maze.hpp"

class ofApp : public ofBaseApp{
    enum GameState {
        IN_PROGRESS = 0,
        PAUSED,
        FINISHED
    };
    GameState current_state = IN_PROGRESS;
    ofSoundPlayer pacmanSiren;
    ofImage pacmanSprite;
    ofImage lol;
    ofImage coin;
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
