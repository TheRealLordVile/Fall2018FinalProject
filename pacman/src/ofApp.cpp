#include "ofApp.h"

//--------------------------------------------------------------
void pacmanGame::setup() {
    srand(static_cast<unsigned>(time(0)));
    level_num = kStartingLevel;
    current_state = START_SCREEN;
    setUpSounds();
    setUpPositions();
    setUpLeaderboardValues();
}

void pacmanGame::setUpPositions() {
    pacman.pos = maze.getInitPacmanPosition();
    ghost_1.pos = maze.getInitGhostPosition(1);
    ghost_2.pos = maze.getInitGhostPosition(2);
    switch (level_num) {
        case 4 ... INT_MAX:
            ghost_5.pos = maze.getInitGhostPosition(5);
        case 3:
            ghost_4.pos = maze.getInitGhostPosition(4);
        case 2:
            ghost_3.pos = maze.getInitGhostPosition(3);
    }
}

void pacmanGame::setUpSounds() {
    start_song.load(kStartSongPath);
    start_song.setVolume(0.9);
    start_song.setLoop(true);

    pacman_siren.load(kPacmanSirenPath);
    pacman_siren.setVolume(0.6);
    pacman_siren.setLoop(true);

    waka_waka.load(kWakaWakaPath);
    waka_waka.setVolume(0.09);
    waka_waka.setLoop(true);
    
    leaderboard_song.load(kLeaderboardSongPath);
    leaderboard_song.setLoop(true);
    
    pacman_dying.load(kPacmanDyingPath);
    
    paused_sound.load(kPausedSoundPath);
    paused_sound.setLoop(true);
    
    ending_song.load(kEndingSongPath);
    ending_song.setLoop(true);
    
}

void pacmanGame::setUpLeaderboardValues() {
    ofFile score_file;
    
    score_file.open(ofToDataPath("scores.json"), ofFile::ReadWrite, true);
    nlohmann::json json;
    json << score_file;
    score_file.close();
    leaderboard = json.get<std::vector<int>>();
}

//--------------------------------------------------------------
void pacmanGame::update() {
    if (current_state == START_SCREEN) {
        if(!start_song.isPlaying()) {
            ofSoundStopAll();
            start_song.play();
        }
        
    } else if (current_state == IN_PROGRESS) {
        if(maze.areAllCoinsEaten()) {
            level_num++;
            loadNewLevel();
        }
        
        if (pacman.num_lives == kPacmanLostNumLives) {
            updateLeaderboard();
            current_state = ENDING_SCREEN;
        }
        
        adjustPacmanSound();
        updatePacman();
        updateGhosts();
    } else if(current_state == PAUSED) {
        if (!paused_sound.isPlaying()) {
            ofSoundStopAll();
            paused_sound.play();
        }
        
    } else if (current_state == LEADERBOARD) {
        if (!leaderboard_song.isPlaying()) {
            ofSoundStopAll();
            leaderboard_song.play();
        }
        
    } else if (current_state == ENDING_SCREEN) {
        if (!ending_song.isPlaying()) {
            ofSoundStopAll();
            ending_song.play();
        }
    }
}

void pacmanGame::updateLeaderboard() {
    int new_score = 100 * (level_num - 1) + maze.getNumberOfCoins()/10;
    leaderboard.push_back(new_score);
    std::sort(leaderboard.begin(), leaderboard.end(), greater<int>());
    if (leaderboard.size() > 10) {
        leaderboard.pop_back();
    }
    
    ofFile score_file;
    score_file.open(ofToDataPath("scores.json"), ofFile::ReadWrite, true);
    nlohmann::json json(leaderboard);
    score_file << json;
    score_file.close();

}

void pacmanGame::loadNewLevel() {
    int num_lives_left = pacman.num_lives;
    maze = Maze{level_num};
    pacman = Pacman();
    pacman.num_lives = num_lives_left;
    ghost_1= Ghost{1};
    ghost_2 = Ghost{2};
    ghost_3 = Ghost{3};
    ghost_4 = Ghost{4};
    ghost_5 = Ghost{5};
    setUpPositions();
    
}

void pacmanGame::updatePacman() {
    std::pair<int,int> new_pos = maze.canPacmanMove(pacman.getDirection(),
                                                    pacman.pos);
    if(new_pos == pacman.pos) {
        pacman.setDirection(Pacman::NONE);
    }
    
    if (!maze.isPacmanAlive()) {
        pacman.num_lives--;
        ofSoundStopAll();
        pacman_dying.play();
        sleep(2);
    }
    
    pacman.pos = new_pos;
}

void pacmanGame::updateGhosts() {
    updateGhost1();
    updateGhost2();
    switch (level_num) {
        case 4 ... INT_MAX:
            updateGhost5();
        case 3:
            updateGhost4();
        case 2:
            updateGhost3();
    }
}

void pacmanGame::updateGhost1() {
    std::pair<int,int> new_pos = maze.canGhostMove(1, ghost_1.getDirection(),
                                                   ghost_1.pos);
    if (new_pos == ghost_1.pos) {
        ghost_1.setDirection(std::rand() % 4);
    
    } else {
        ghost_1.pos = new_pos;
    }
    

}

void pacmanGame::updateGhost2() {
    std::pair<int,int> new_pos = maze.canGhostMove(2, ghost_2.getDirection(),
                                                   ghost_2.pos);
    if (new_pos == ghost_2.pos) {
        ghost_2.setDirection(std::rand() % 4);
    
    } else {
        ghost_2.pos = new_pos;
    
    }
}

void pacmanGame::updateGhost3() {
   std::pair<int,int> new_pos = maze.canGhostMove(3, ghost_3.getDirection(),
                                                  ghost_3.pos);
    if (new_pos == ghost_3.pos) {
        ghost_3.setDirection(std::rand() % 4);
    
    } else {
        ghost_3.pos = new_pos;
    }
}

void pacmanGame::updateGhost4() {
    std::pair<int,int> new_pos = maze.canGhostMove(4, ghost_4.getDirection(),
                                                   ghost_4.pos);
    if (new_pos == ghost_4.pos) {
        ghost_4.setDirection(std::rand() % 4);
        
    } else {
        ghost_4.pos = new_pos;
    }
}

void pacmanGame::updateGhost5() {
    std::pair<int,int> new_pos = maze.canGhostMove(5, ghost_5.getDirection(),
                                                   ghost_5.pos);
    if (new_pos == ghost_5.pos) {
        ghost_5.setDirection(std::rand() % 4);
        
    } else {
        ghost_5.pos = new_pos;
    }
}


void pacmanGame::adjustPacmanSound() {
    if (!pacman_siren.isPlaying()) {
        ofSoundStopAll();
        pacman_siren.play();
    }
    
    if (pacman.getDirection() == Pacman::NONE) {
        waka_waka.stop();
    
    } else {
        if (!waka_waka.isPlaying()) {
            waka_waka.play();
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
        
    } else if(current_state == LEADERBOARD) {
        drawLeaderboard();
        
    } else if (current_state == ENDING_SCREEN) {
        ofSoundStopAll();
        drawEndingScreen();
    }
}

void pacmanGame::drawStartScreen(){
    ofImage start_screen;
    start_screen.load(kStartScreenImgPath);
    start_screen.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    ofPath start_rect;
    ofPath leaderboard_rect;
    
    start_button = ofRectangle (2*ofGetWindowWidth()/5,
                                29 * ofGetWindowHeight()/40,ofGetWindowWidth() / 5, ofGetWindowHeight() / 20);
    leaderboard_button = ofRectangle(2*ofGetWindowWidth()/5,
                                     67 * ofGetWindowHeight() / 80,
                                     ofGetWindowWidth()/5, ofGetWindowHeight()/20);
    
    leaderboard_rect.rectangle(leaderboard_button);
    leaderboard_rect.setColor(ofColor(25,25,112));
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    
    start_rect.rectangle(start_button);
    start_rect.setColor(ofColor(25,25,112));
    start_rect.setFilled(true);
    start_rect.draw();
    
    string play_message = "PLAY!";
    string leaderboard_message = "LEADERBOARD";
    ofDrawBitmapString(play_message, ofGetWindowWidth()/2-ofGetWindowWidth()/40,
                       3 * ofGetWindowHeight()/4+ofGetWindowHeight()/200);
    ofDrawBitmapString(leaderboard_message,
                       ofGetWindowWidth()/2-ofGetWindowWidth()/18,
                       3 * ofGetWindowHeight() / 4
                       + ofGetWindowHeight()/9);
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
            } else if (element == Maze::mazeElement::GHOST4) {
                ghost_4.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
            }else if (element == Maze::mazeElement::GHOST5) {
                ghost_5.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
            }
        }
    }
}

void pacmanGame::drawPauseScreen() {
    drawGameState();
    string pause_message = "Press P to Unpause! \n" +std::to_string(maze.getNumberOfCoins());
    ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    
}

void pacmanGame::drawLeaderboard() {
    ofRectangle background(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    ofPath colored_background;
    colored_background.rectangle(background);
    colored_background.setColor(ofColor(25,25,80));
    colored_background.setFilled(true);
    colored_background.draw();
    
    ofImage leaderboard_frame;
    leaderboard_frame.load(kLeaderboardImgPath);
    leaderboard_frame.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    
    ofTrueTypeFont end_font;
    end_font.load(OF_TTF_SANS, 0.02 * ofGetWindowHeight()+ 0.02 * ofGetWindowWidth());
    string leaderboard_message = "LEADERBOARD \n\n";
    for (int i=0; i< leaderboard.size(); i++) {
        // Add two extra empty spaces to all lines except the one that starts
        // with 10 to align them.
        if (i + 1 != 10) {
            leaderboard_message += "  ";
        }
        
        leaderboard_message += "     " + std::to_string(i + 1) + ".) " + std::to_string(leaderboard[i]) + "\n";
    }
    ofSetColor(255,255,0);
    end_font.drawString(leaderboard_message, ofGetWindowWidth() / 2 - end_font.stringWidth(leaderboard_message)/2, ofGetWindowHeight() / 10);
    ofSetColor(255,255,255);
    ofPath leaderboard_rect;
    leaderboard_rect.rectangle(leaderboard_button);
    leaderboard_rect.setColor(ofColor(0,0,0));
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    ofDrawBitmapString("START SCREEN",
                       ofGetWindowWidth()/2-ofGetWindowWidth()/18,
                       3 * ofGetWindowHeight() / 4
                       + ofGetWindowHeight()/9);
}

void pacmanGame::drawEndingScreen() {
    ofImage ending_background;
    ending_background.load(kEndingImgPath);
    ending_background.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    ofImage game_over;
    game_over.load(kGameOverImgPath);
    game_over.draw(3 * ofGetWindowWidth()/5, ofGetWindowHeight()/6,
                   ofGetWindowWidth()/7, ofGetWindowHeight()/7);
    ofPath leaderboard_rect;
    leaderboard_rect.rectangle(leaderboard_button);
    leaderboard_rect.setColor(ofColor(0,0,0));
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    ofDrawBitmapString("SEE THE LEADERBOARD",
                        ofGetWindowWidth()/2-ofGetWindowWidth()/18,
                        3 * ofGetWindowHeight() / 4
                        + ofGetWindowHeight()/9);
}

//--------------------------------------------------------------
void pacmanGame::keyPressed(int key){
    int upper_key = toupper(key);
    if(upper_key=='P' && (current_state == IN_PROGRESS ||
                          current_state == PAUSED)){
        current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
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
    if (current_state == START_SCREEN) {
        if (start_button.inside(x, y)) {
            current_state = IN_PROGRESS;
            start_song.stop();
            
        } else if (leaderboard_button.inside(x, y)) {
            ofSoundStopAll();
            current_state = LEADERBOARD;
        }
    } else if (current_state == LEADERBOARD) {
        if (leaderboard_button.inside(x, y)) {
            current_state = START_SCREEN;
        }
    } else if (current_state == ENDING_SCREEN) {
        if (leaderboard_button.inside(x, y)) {
            current_state = LEADERBOARD;
            level_num  = kStartingLevel;
            loadNewLevel();
            pacman.num_lives = kPacmanStartingNumLives;
        }
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
