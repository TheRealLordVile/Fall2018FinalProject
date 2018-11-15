#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    lol.load("/Users/a.kadri/Desktop/PacmanLevel-1-925x1024.png");
    coin.load("/Users/a.kadri/Desktop/Euro-Coin-128.png");
    pacmanSprite.load("/Users/a.kadri/Desktop/image.png");
    pacmanSiren.load("/Users/a.kadri/Desktop/SFX_Pacman/Siren.mp3");
    pacmanSiren.setLoop(true);
    pacmanSiren.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (current_state == IN_PROGRESS) {
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    lol.draw(0, 0,ofGetWindowWidth(),ofGetWindowHeight());
    Maze new_maze;
    new_maze.layout;
    int height = new_maze.layout.size();
    int width = new_maze.layout[0].size();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width ;j++){
            if(new_maze.layout[i][j] == Maze::mazeElement::COIN){
                coin.draw(j*ofGetWindowWidth()/width + 10, i*ofGetWindowHeight()/height+10,10,10);
            } else if(new_maze.layout[i][j] == Maze::mazeElement::PACMAN){
                pacmanSprite.draw(j*ofGetWindowWidth()/width -15, i*ofGetWindowHeight()/height-10,40,40);
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
