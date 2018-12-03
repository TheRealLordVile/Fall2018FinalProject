#include "ofApp.h"

//--------------------------------------------------------------
void pacmanGame::setup() {
    pacmanSiren.load("../../sounds/Siren.mp3");
    pacmanSiren.setLoop(true);
    pacmanSiren.play();
    srand(static_cast<unsigned>(time(0)));

}

//--------------------------------------------------------------
void pacmanGame::update() {
    if (current_state == IN_PROGRESS) {
        updatePacman();
    }
}

void pacmanGame::updatePacman() {
    pacman.pos=maze.canPacmanMove(pacman.getDirection(),pacman.pos.first,pacman.pos.second);
    
}

//--------------------------------------------------------------
void pacmanGame::draw() {
    if(current_state == IN_PROGRESS){
        maze.getBackground().draw(0, 0,ofGetWindowWidth(),ofGetWindowHeight());
        int height = maze.getMazeHeight();
        int width = maze.getMazeWidth();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
            if (maze.getElementAt(i,j) == Maze::mazeElement::COIN){
                maze.getCoinSprite().draw(j * ofGetWindowWidth() / width,
                                          i * ofGetWindowHeight() / height,
                                          ofGetWindowWidth() / width,
                                          ofGetWindowHeight() / height);
                
            }
            else if(maze.getElementAt(i,j) == Maze::mazeElement::PACMAN){
                
                double x_loc = j * ofGetWindowWidth()/width-ofGetWindowWidth()/
                              width / 3;
                double y_loc = i * ofGetWindowHeight()/height-ofGetWindowHeight()
                              / height / 5;
                double x_size = 3 * ofGetWindowWidth() / width / 2;
                double y_size = 4 * ofGetWindowHeight() / height / 3;
                pacman.getPacmanSprite().draw(x_loc, y_loc,x_size,y_size);
            }
            }
        }
    }
}

//--------------------------------------------------------------
void pacmanGame::keyPressed(int key){
    int upper_key = toupper(key);
    switch (upper_key) {
        case 'W':
            if( pacman.getDirection() != Pacman::DOWN) {
                pacman.setDirection(Pacman::UP);
            }
            break;
        case 'S':
            if( pacman.getDirection() != Pacman::UP) {
                pacman.setDirection(Pacman::DOWN);
            }
            break;
        case 'A':
            if( pacman.getDirection() != Pacman::RIGHT) {
                pacman.setDirection(Pacman::LEFT);
            }
            break;
        case 'D':
            if( pacman.getDirection() != Pacman::LEFT) {
                pacman.setDirection(Pacman::RIGHT);
            }
            break;
    }
}

//--------------------------------------------------------------
void pacmanGame::keyReleased(int key){

}

//--------------------------------------------------------------
void pacmanGame::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void pacmanGame::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void pacmanGame::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void pacmanGame::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void pacmanGame::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void pacmanGame::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void pacmanGame::windowResized(int w, int h){

}

//--------------------------------------------------------------
void pacmanGame::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void pacmanGame::dragEvent(ofDragInfo dragInfo){ 

}
