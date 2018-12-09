#include "ofApp.h"

//--------------------------------------------------------------
void pacmanGame::setup() {
    ofSetFrameRate(7);
    setUpSounds();
    srand(static_cast<unsigned>(time(0)));
}

void pacmanGame::setUpSounds() {
    start_song.load("../../sounds/start_song.mp3");
    start_song.setVolume(0.9);
    
    pacman_siren.load("../../sounds/Siren.mp3");
    pacman_siren.setVolume(0.6);
    
    waka_waka.load("../../sounds/PacmanWakaWaka.wav");
    waka_waka.setVolume(0.09);
    
    start_song.setLoop(true);
    waka_waka.setLoop(true);
    pacman_siren.setLoop(true);
    
    start_song.play();
}

//--------------------------------------------------------------
void pacmanGame::update() {
    if(current_state == IN_PROGRESS) {
        if(maze.areAllCoinsEaten() || pacman.num_lives <= 0) {
            current_state = FINISHED;
        }
        updatePacman();
        updateGhosts();
        
        adjustPacmanSound();
    }
}

void pacmanGame::updatePacman() {
    std::pair<int,int> new_pos = maze.canPacmanMove(pacman.getDirection(),
                                                    pacman.pos);
    if(new_pos == pacman.pos) {
        pacman.setDirection(Pacman::NONE);
    }
    if (!maze.isPacmanAlive()) {
        pacman.num_lives--;
    }
    
    pacman.pos = new_pos;
}

void pacmanGame::updateGhosts() {
    updateGhost1();
    //updateGhost2();
    //updateGhost3();
}

void pacmanGame::updateGhost1() {
    std::pair<int,int> new_pos = maze.canGhostMove(1, ghost_1.getDirection(), ghost_1.pos);
    
    if (new_pos == ghost_1.pos) {
        ghost_1.setDirection(std::rand() % 4);
    } else {
        ghost_1.pos = new_pos;
    }
    

}

void pacmanGame::updateGhost2() {
    std::pair<int,int> new_pos = maze.canGhostMove(2, ghost_2.getDirection(), ghost_2.pos);
    if (new_pos == ghost_2.pos) {
        ghost_2.setDirection(std::rand() % 4);
    } else {
        ghost_2.pos = new_pos;
    }
}

void pacmanGame::updateGhost3() {
   std::pair<int,int> new_pos = maze.canGhostMove(3, ghost_3.getDirection(), ghost_3.pos);
    if (new_pos == ghost_3.pos) {
        ghost_3.setDirection(std::rand() % 4);
    } else {
        ghost_3.pos = new_pos;
    }
}

void pacmanGame::adjustPacmanSound() {
    if (pacman.getDirection() == Pacman::NONE) {
        waka_waka.stop();
    } else {
        if (waka_waka.isPlaying() == false) {
            waka_waka.play();
            waka_waka.setLoop(true);
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
    //rectangle.inside
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
            double x_loc = j * ofGetWindowWidth()/width-ofGetWindowWidth()/
            width / 3;
            double y_loc = i * ofGetWindowHeight()/height -
            ofGetWindowHeight() /  height / 5;
            double x_size = 3 * ofGetWindowWidth() / width / 2;
            double y_size = 4 * ofGetWindowHeight() / height / 3;
            Maze::mazeElement element = maze.getElementAt(i,j);
            if (element == Maze::mazeElement::COIN) {
                maze.getCoinSprite().draw(j * ofGetWindowWidth() / width,
                                          i * ofGetWindowHeight() / height,
                                          ofGetWindowWidth() / width,
                                          ofGetWindowHeight() / height);
                
            } else if(element == Maze::mazeElement::PACMAN) {
                pacman.getPacmanSprite().draw(x_loc, y_loc,x_size,y_size);
            } else if (element == Maze::mazeElement::GHOST1) {
                ghost_1.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
            } else if (element == Maze::mazeElement::GHOST2) {
                ghost_2.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
            } else if (element == Maze::mazeElement::GHOST3) {
                ghost_3.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
            }
        }
    }
}

void pacmanGame::drawPauseScreen() {
    drawGameState();
    string pause_message = "Press P to Unpause! \n" +std::to_string(maze.getNumberOfCoins());
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
}

//--------------------------------------------------------------
void pacmanGame::keyPressed(int key){
    int upper_key = toupper(key);
    if(upper_key=='P' && (current_state == IN_PROGRESS ||
                          current_state == PAUSED)){
        current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
        if(pacman_siren.isPlaying()) {
            pacman_siren.stop();
            waka_waka.stop();
        } else {
            pacman_siren.play();
            pacman_siren.setLoop(true);
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
        start_song.stop();
        pacman_siren.play();
        waka_waka.play();
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
