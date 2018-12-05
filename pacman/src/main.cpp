#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_WINDOW

int main() {
    ofSetupOpenGL(780, 740, DISPLAY_MODE);
    ofSetFrameRate(5);
    ofRunApp(new pacmanGame());
}
