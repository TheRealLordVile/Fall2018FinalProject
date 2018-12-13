#include "ofApp.h"

//--------------------------------------------------------------
void pacmanGame::setup() {
    srand(static_cast<unsigned>(time(0)));
    level_num = kStartingLevel;
    current_state = START_SCREEN;
    setUpSounds();
    setUpPositions();
    setUpLeaderboardValues();
    setUpButtonRectangles();
}

void pacmanGame::setUpPositions() {
    pacman.setPos(maze.getInitPacmanPosition());
    ghost_1.setPos(maze.getInitGhostPosition(kGhost1Index));
    ghost_2.setPos(maze.getInitGhostPosition(kGhost2Index));
    switch (level_num) {
            // By using 4...INT_MAX, any value above 3 will be in this case.
        case 4 ... INT_MAX:
            ghost_5.setPos(maze.getInitGhostPosition(kGhost5Index));
        case 3:
            ghost_4.setPos(maze.getInitGhostPosition(kGhost4Index));
        case 2:
            ghost_3.setPos(maze.getInitGhostPosition(kGhost3Index));
    }
}

void pacmanGame::setUpSounds() {
    start_song.load(kStartSongPath);
    start_song.setVolume(kStartSoundVol);
    start_song.setLoop(true);

    pacman_siren.load(kPacmanSirenPath);
    pacman_siren.setVolume(kPacmanSirenVol);
    pacman_siren.setLoop(true);

    waka_waka.load(kWakaWakaPath);
    waka_waka.setVolume(kWakaWakaSoundVol);
    waka_waka.setLoop(true);
    
    leaderboard_song.load(kLeaderboardSongPath);
    
    pacman_dying.load(kPacmanDyingPath);
    
    paused_sound.load(kPausedSoundPath);
    paused_sound.setLoop(true);
    
    ending_song.load(kEndingSongPath);
    ending_song.setVolume(kEndingSongVol);
}

void pacmanGame::setUpLeaderboardValues() {
    // A json file is used to store the top score values.
    ofFile score_file;
    score_file.open(ofToDataPath(kTopScoresDataPath), ofFile::ReadWrite, true);
    nlohmann::json json;
    json << score_file;
    score_file.close();
    leaderboard = json.get<std::vector<int>>();
}

void pacmanGame::setUpButtonRectangles() {
    start_button = ofRectangle(kButtonXMultiplier * ofGetWindowWidth(),
                               kStartButtonYMultiplier * ofGetWindowHeight(),
                               kButtonWidthMultiplier * ofGetWindowWidth(),
                               kButtonHeightMultiplier * ofGetWindowHeight());
    
    leaderboard_button = ofRectangle(kButtonXMultiplier * ofGetWindowWidth(),
                                     kLeaderboardButtonYMultiplier *
                                     ofGetWindowHeight(),
                                     kButtonWidthMultiplier *
                                     ofGetWindowWidth(),
                                     kButtonHeightMultiplier *
                                     ofGetWindowHeight());
}

//--------------------------------------------------------------
void pacmanGame::update() {
    switch (current_state) {
        case START_SCREEN:
            if (!start_song.isPlaying()) {
                ofSoundStopAll();
                start_song.play();
            }
            
            break;
        case IN_PROGRESS:
            if (maze.areAllCoinsEaten()) {
                level_num++;
                loadNewLevel();
            }
            
            if (pacman.getNumLives() == kPacmanLostNumLives) {
                updateLeaderboard();
                current_state = ENDING_SCREEN;
            }
            
            updatePacmanSound();
            updatePacman();
            updateGhosts();
            break;
        case PAUSED:
            if (!paused_sound.isPlaying()) {
                ofSoundStopAll();
                paused_sound.play();
            }
            
            break;
        case LEADERBOARD:
            if (!leaderboard_song.isPlaying()) {
                ofSoundStopAll();
                leaderboard_song.play();
            }
            
            break;
        case ENDING_SCREEN:
            if (!ending_song.isPlaying()) {
                ofSoundStopAll();
                ending_song.play();
            }
    }
}

void pacmanGame::updatePacmanSound() {
    if (!pacman_siren.isPlaying()) {
        ofSoundStopAll();
        pacman_siren.play();
    }
    
    // Waka waka is played when pacman is moving.
    if (pacman.getDirection() == Pacman::NONE) {
        waka_waka.stop();
        
    } else {
        if (!waka_waka.isPlaying()) {
            waka_waka.play();
        }
    }
}

void pacmanGame::updatePacman() {
    std::pair<int,int> new_pos = maze.canPacmanMove(pacman.getDirection(),
                                                    pacman.getPos());
    if (new_pos == pacman.getPos()) {
        pacman.setDirection(Pacman::NONE);
    }
    
    // Number of lives is decreased by one when pacman dies.
    // And the dying sound is played
    if (!maze.isPacmanAlive()) {
        pacman.setNumLives(pacman.getNumLives() - 1);
        ofSoundStopAll();
        pacman_dying.play();
        sleep(kPacmanDiedWaitTime);
    }
    
    pacman.setPos(new_pos);
}

void pacmanGame::updateGhosts() {
    updateGhostPosition(ghost_1, kGhost1Index);
    updateGhostPosition(ghost_2, kGhost2Index);
    switch (level_num) {
        case 4 ... INT_MAX:
            updateGhostPosition(ghost_5, kGhost5Index);
        case 3:
            updateGhostPosition(ghost_4, kGhost4Index);
        case 2:
            updateGhostPosition(ghost_3, kGhost3Index);
    }
}

void pacmanGame::updateGhostPosition(Ghost &ghost, int ghost_index) {
    std::pair<int,int> new_pos = maze.canGhostMove(ghost_index,
                                                   ghost.getDirection(),
                                                   ghost.getPos());
    if (new_pos == ghost.getPos()) {
        ghost.setDirection(std::rand() % kNumGhostDirections);
    
    } else {
        ghost.setPos(new_pos);
    }
}

void pacmanGame::updateLeaderboard() {
    int new_score = kPointsPerLevelPassed * (level_num - kStartingLevel);
    new_score += kPointsPerCoin * maze.getNumberOfCoins();
    leaderboard.push_back(new_score);
    std::sort(leaderboard.begin(), leaderboard.end(), greater<int>());
    
    if (leaderboard.size() > kMaxNumScores) {
        leaderboard.pop_back();
    }
    
    ofFile score_file;
    score_file.open(ofToDataPath(kTopScoresDataPath), ofFile::ReadWrite, true);
    nlohmann::json json(leaderboard);
    score_file << json;
    score_file.close();
}

void pacmanGame::loadNewLevel() {
    int num_lives_left = pacman.getNumLives();
    maze = Maze{level_num};
    pacman = Pacman();
    pacman.setNumLives(num_lives_left);
    ghost_1= Ghost{kGhost1Index};
    ghost_2 = Ghost{kGhost2Index};
    ghost_3 = Ghost{kGhost3Index};
    ghost_4 = Ghost{kGhost4Index};
    ghost_5 = Ghost{kGhost5Index};
    setUpPositions();
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
        drawEndingScreen();
    }
}

void pacmanGame::drawStartScreen(){
    // The backgroung image, the button rectangles and their strings are drawn
    // in that order.
    ofImage start_screen;
    start_screen.load(kStartScreenImgPath);
    start_screen.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    ofPath start_rect;
    ofPath leaderboard_rect;
    
    leaderboard_rect.rectangle(leaderboard_button);
    leaderboard_rect.setColor(kStartScreenButtonColor);
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    
    start_rect.rectangle(start_button);
    start_rect.setColor(kStartScreenButtonColor);
    start_rect.setFilled(true);
    start_rect.draw();
    
    ofDrawBitmapString(kPlayMessageString,
                       kStartButtonStringXMultiplier * ofGetWindowWidth(),
                       kStartButtonStringYMultiplier * ofGetWindowHeight());
    
    ofDrawBitmapString(kLeaderboardMessageString,
                       kLeaderboardButtonStringXMultiplier * ofGetWindowWidth(),
                       kLeaderboardButtonStringYMultiplier *
                       ofGetWindowHeight());
}

void pacmanGame::drawGameState() {
    // The background image of the maze is drawn.
    maze.getBackground().draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    int height = maze.getMazeHeight();
    int width = maze.getMazeWidth();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // The default x and y locations and sizes for everything except the
            // coins, which are sized and placed differently.
            double x_loc = (j - kElementXOffsetMultiplier) *
                           ofGetWindowWidth() / width;
            
            double y_loc = (i - kElementYOffsetMultiplier) *
                           ofGetWindowHeight() / height;
            
            double x_size = kElementSizeMultiplier * ofGetWindowWidth() / width;
            double y_size = kElementSizeMultiplier * ofGetWindowHeight()
                            / height;
            
            switch (maze.getElementAt(i,j)) {
                    
                case Maze::mazeElement::COIN:
                    maze.getCoinSprite().draw(j * ofGetWindowWidth() / width,
                                              i * ofGetWindowHeight() / height,
                                              ofGetWindowWidth() / width,
                                              ofGetWindowHeight() / height);
                    break;
                    
                case Maze::mazeElement::PACMAN:
                    pacman.getPacmanSprite().draw(x_loc, y_loc,x_size,y_size);
                    break;
                    
                case Maze::mazeElement::GHOST1:
                    ghost_1.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
                    break;
                    
                case Maze::mazeElement::GHOST2:
                    ghost_2.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
                    break;
                    
                case Maze::mazeElement::GHOST3:
                    ghost_3.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
                    break;
                    
                case Maze::mazeElement::GHOST4:
                    ghost_4.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
                    break;
                    
                case Maze::mazeElement::GHOST5:
                    ghost_5.getGhostSprite().draw(x_loc, y_loc,x_size,y_size);
                    break;
            }
        }
    }
}

void pacmanGame::drawPauseScreen() {
    drawGameState();
    std::string pause_message = kPauseString1;
    pause_message += std::to_string(pacman.getNumLives());
    pause_message += kPauseString2;
    
    ofDrawBitmapString(pause_message, kPauseScreenMessageX * ofGetWindowWidth(),
                       kPauseScreenMessageY * ofGetWindowHeight());
}

void pacmanGame::drawLeaderboard() {
    // The background color is drawn.
    ofRectangle background(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofPath colored_background;
    colored_background.rectangle(background);
    colored_background.setColor(kLeaderboardScreenBackgroundColor);
    colored_background.setFilled(true);
    colored_background.draw();
    
    // The frame is drawn.
    ofImage leaderboard_frame;
    leaderboard_frame.load(kLeaderboardImgPath);
    leaderboard_frame.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    
    // A TrueTypeFont is created to change the size of the string and to be
    // able to set a color to it.
    ofTrueTypeFont end_font;
    end_font.load(OF_TTF_SANS, kFontSizeMultiplier *
                  (ofGetWindowHeight() + ofGetWindowWidth()));
    
    ofSetColor(kLeaderBoardStringColor);
    end_font.drawString(getLeaderboardMessage(),
                        kXLocMultiplier * ofGetWindowWidth(),
                        kYLocMultiplier * ofGetWindowHeight());
    ofSetColor(kDefaultColor);
    
    ofPath leaderboard_rect;
    leaderboard_rect.rectangle(leaderboard_button);
    leaderboard_rect.setColor(kLeaderboardEndingButtonColor);
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    ofDrawBitmapString(kStartMessageString,
                       kLeaderboardButtonStringXMultiplier * ofGetWindowWidth(),
                       kLeaderboardButtonStringYMultiplier *
                       ofGetWindowHeight());
}

void pacmanGame::drawEndingScreen() {
    // The background image, game over image, the button rectange and its string
    // is drawn in that order.
    ofImage ending_background;
    ending_background.load(kEndingImgPath);
    ending_background.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    ofImage game_over;
    game_over.load(kGameOverImgPath);
    game_over.draw(kGameOverXPosMultiplier * ofGetWindowWidth(),
                   kGameOverYPosMultiplier * ofGetWindowHeight(),
                   kGameOverSizeMultiplier * ofGetWindowWidth(),
                   kGameOverSizeMultiplier * ofGetWindowHeight()/7);
    ofPath leaderboard_rect;
    leaderboard_rect.rectangle(leaderboard_button);
    leaderboard_rect.setColor(kLeaderboardEndingButtonColor);
    leaderboard_rect.setFilled(true);
    leaderboard_rect.draw();
    ofDrawBitmapString(kLeaderboardMessageString,
                       kLeaderboardButtonStringXMultiplier * ofGetWindowWidth(),
                       kLeaderboardButtonStringYMultiplier *
                       ofGetWindowHeight());
}

std::string pacmanGame::getLeaderboardMessage() {
    std::string leaderboard_msg = kLeaderboardString1;
    for (int i = 0; i < leaderboard.size(); i++) {
        // Add two extra empty spaces to all lines except the one that starts
        // with 10 to align them.
        if (i + 1 != kMaxNumScores) {
            leaderboard_msg += kLeaderboardString2;
        }
        
        leaderboard_msg += kLeaderboardString3;
        // i+1 ranges from 1 to 10, representing the place of each score.
        leaderboard_msg += std::to_string(i + 1);
        leaderboard_msg += kLeaderboardString4;
        leaderboard_msg += std::to_string(leaderboard[i]) + "\n";
    }
    
    return leaderboard_msg;
}

//--------------------------------------------------------------
void pacmanGame::keyPressed(int key) {
    int upper_key = toupper(key);
    if (upper_key == kPauseButton && (current_state == IN_PROGRESS ||
                                      current_state == PAUSED)) {
        
        current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
    }
    
    if (current_state == IN_PROGRESS) {
        switch (upper_key) {
            case kUpButton:
                if (pacman.getDirection() != Pacman::DOWN) {
                    pacman.setDirection(Pacman::UP);
                }
                
                break;
            case kDownButton:
                if (pacman.getDirection() != Pacman::UP) {
                    pacman.setDirection(Pacman::DOWN);
                }
                
                break;
            case kLeftButton:
                if (pacman.getDirection() != Pacman::RIGHT) {
                    pacman.setDirection(Pacman::LEFT);
                }
                break;
            case kRightButton:
                if (pacman.getDirection() != Pacman::LEFT) {
                    pacman.setDirection(Pacman::RIGHT);
                }
                
                break;
        }
    }
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
            pacman.setNumLives(kPacmanStartingNumLives);
        }
    }
}

//--------------------------------------------------------------
void pacmanGame::windowResized(int w, int h){
    // Button rectangle sizes are updated when the window is resized.
    setUpButtonRectangles();
}

void pacmanGame::gotMessage(ofMessage msg){}
void pacmanGame::dragEvent(ofDragInfo dragInfo){}
void pacmanGame::mouseReleased(int x, int y, int button){}
void pacmanGame::mouseEntered(int x, int y){}
void pacmanGame::mouseExited(int x, int y){}
void pacmanGame::keyReleased(int key){}
void pacmanGame::mouseMoved(int x, int y ){}
void pacmanGame::mouseDragged(int x, int y, int button){}
