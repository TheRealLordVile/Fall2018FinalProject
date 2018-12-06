#include "ofApp.h"

//--------------------------------------------------------------
void pacmanGame::setup() {
    ofSetFrameRate(7);
    setUpSounds();
    srand(static_cast<unsigned>(time(0)));
}

void pacmanGame::setUpSounds() {
    pacmanSiren.load("../../sounds/Siren.mp3");
    pacmanSiren.setVolume(0.6);
    wakaWaka.load("../../sounds/PacmanWakaWaka.wav");
    wakaWaka.setVolume(0.09);
    wakaWaka.play();
    wakaWaka.setLoop(true);
    pacmanSiren.setLoop(true);
    pacmanSiren.play();
}

//--------------------------------------------------------------
void pacmanGame::update() {
    if (current_state == START_SCREEN) {
        
    }  else if(current_state == IN_PROGRESS) {
        updatePacman();
        adjustPacmanSound();
    }
}

void pacmanGame::updatePacman() {
    std::pair<int,int> new_pos = maze.canPacmanMove(pacman.getDirection(),pacman.pos);
    if(new_pos == pacman.pos){
        pacman.setDirection(Pacman::NONE);
    }
    pacman.pos = new_pos;
}

void pacmanGame::adjustPacmanSound() {
    if (pacman.getDirection() == Pacman::NONE) {
        wakaWaka.stop();
    } else {
        if (wakaWaka.isPlaying() == false) {
            wakaWaka.play();
            wakaWaka.setLoop(true);
        }
    }
    
}


//--------------------------------------------------------------
void pacmanGame::draw() {
    
    if (current_state == START_SCREEN) {
        drawStartScreen();
    } else if (current_state == IN_PROGRESS) {
        drawGameState();
        } else if (current_state == PAUSED) {
        drawPauseScreen();
    }
}

void pacmanGame::drawStartScreen(){
    ofImage start_screen_1;
    start_screen_1.load("../../images/start_screen_1.jpg");
    start_screen_1.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    
    ofPath start_rect;
    ofPath leaderboard_rect;
    start_coord_x.first = ofGetWindowWidth()/2-ofGetWindowWidth()/10;
    start_coord_x.second = ofGetWindowWidth()/2-ofGetWindowWidth()/10 + ofGetWindowWidth()/5;
    start_coord_y.first = 3 * ofGetWindowHeight()/4-ofGetWindowHeight()/40;
    start_coord_y.second = 3 * ofGetWindowHeight()/4-ofGetWindowHeight()/40 +ofGetWindowHeight()/20;
    ofRectangle start(start_coord_x.first, start_coord_y.first,
                      ofGetWindowWidth()/5, ofGetWindowHeight()/20);
    leader_coord_x.first = ofGetWindowWidth()/2-ofGetWindowWidth()/10;
    leader_coord_x.second = ofGetWindowWidth()/2-ofGetWindowWidth()/10 + ofGetWindowWidth()/5;
    leader_coord_y.first = 3 * ofGetWindowHeight()/4-ofGetWindowHeight()/40+ofGetWindowHeight()/10;
    leader_coord_y.second =3 * ofGetWindowHeight()/4-ofGetWindowHeight()/40+ofGetWindowHeight()/10+ ofGetWindowHeight()/20;
    
    ofRectangle leaderboard(leader_coord_x.first, leader_coord_y.first,
                            ofGetWindowWidth()/5, ofGetWindowHeight()/20);
    leaderboard_rect.rectangle(leaderboard);
    leaderboard_rect.setColor(ofColor(25,25,112));
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    
    start_rect.rectangle(start);
    start_rect.setColor(ofColor(25,25,112));
    start_rect.setFilled(true);
    start_rect.draw();
    
    string play_message = "PLAY!";
    string leaderboard_message = "Leaderboard";
    ofDrawBitmapString(play_message, ofGetWindowWidth()/2-ofGetWindowWidth()/40, 3 * ofGetWindowHeight()/4+ofGetWindowHeight()/200);
}

void pacmanGame::drawGameState() {
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
            else if(maze.getElementAt(i,j) == Maze::mazeElement::PACMAN) {
                double x_loc = j * ofGetWindowWidth()/width-ofGetWindowWidth()/
                width / 3;
                double y_loc = i * ofGetWindowHeight()/height -
                               ofGetWindowHeight() /  height / 5;
                double x_size = 3 * ofGetWindowWidth() / width / 2;
                double y_size = 4 * ofGetWindowHeight() / height / 3;
                pacman.getPacmanSprite().draw(x_loc, y_loc,x_size,y_size);
                
            }
        }
    }
}

void pacmanGame::drawPauseScreen() {
    drawGameState();
    string pause_message = "Press P to Unpause!";
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
}

//--------------------------------------------------------------
void pacmanGame::keyPressed(int key){
    int upper_key = toupper(key);
    if(upper_key=='P' && (current_state == IN_PROGRESS ||
                          current_state == PAUSED)){
        current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
        if(pacmanSiren.isPlaying()) {
            pacmanSiren.stop();
            wakaWaka.stop();
        } else {
            pacmanSiren.play();
            pacmanSiren.setLoop(true);
        }
    }
    
    if (current_state == IN_PROGRESS) {
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
    bool is_start_x = x <= start_coord_x.second && start_coord_x.first <=x;
    bool is_start_y = y <= start_coord_y.second && start_coord_y.first <=y;

    if (is_start_x && is_start_y) {
        current_state = IN_PROGRESS;
    }
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
