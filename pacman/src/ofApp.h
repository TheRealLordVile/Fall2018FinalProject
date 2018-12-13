#pragma once
#include <cstdlib>
#include "maze.hpp"
#include "pacman.hpp"
#include "ghost.hpp"

class pacmanGame : public ofBaseApp {
    // The enums represent the current state of the game.
    enum GameState {
        START_SCREEN,
        IN_PROGRESS,
        PAUSED,
        LEADERBOARD,
        ENDING_SCREEN
    };
    
    // The constants ordered by their type.
    const std::string kStartSongPath = "../../sounds/start_song.mp3";
    const std::string kPacmanSirenPath = "../../sounds/Siren.mp3";
    const std::string kWakaWakaPath = "../../sounds/PacmanWakaWaka.wav";
    const std::string kLeaderboardSongPath ="../../sounds/leaderboard_song.mp3";
    const std::string kPacmanDyingPath = "../../sounds/pacman_dies_sound.mp3";
    const std::string kPausedSoundPath = "../../sounds/pacman_intermission.mp3";
    const std::string kEndingSongPath = "../../sounds/ending_song.mp3";
    const std::string kStartScreenImgPath = "../../images/start_screen.jpg";
    const std::string kLeaderboardImgPath ="../../images/leaderboard_frame.png";
    const std::string kEndingImgPath = "../../images/ending_background.jpg";
    const std::string kGameOverImgPath = "../../images/game_over.png";
    const std::string kTopScoresDataPath = "scores.json";
    
    const std::string kPlayMessageString = "PLAY!";
    const std::string kLeaderboardMessageString = "LEADERBOARD";
    const std::string kStartMessageString = "START SCREEN";
    const std::string kPauseString1 = "  Press P to Unpause! \nYou have ";
    const std::string kPauseString2 = " lives left";
    const std::string kLeaderboardString1 = "LEADERBOARD \n\n";
    const std::string kLeaderboardString2 = "  ";
    const std::string kLeaderboardString3 = "     ";
    const std::string kLeaderboardString4 = ".) ";
    const std::string kLeaderboardString5 = ".) ";
    
    const double kButtonXMultiplier = 0.4;
    const double kStartButtonYMultiplier = 0.725;
    const double kLeaderboardButtonYMultiplier = 0.8375;
    const double kButtonWidthMultiplier = 0.2;
    const double kButtonHeightMultiplier = 0.05;
    const double kStartButtonStringXMultiplier = 0.475;
    const double kStartButtonStringYMultiplier = 0.755;
    const double kLeaderboardButtonStringXMultiplier = 0.44444444444;
    const double kLeaderboardButtonStringYMultiplier = 0.86111111111;
    const double kStartSoundVol = 0.9;
    const double kPacmanSirenVol = 0.6;
    const double kWakaWakaSoundVol = 0.09;
    const double kEndingSongVol = 0.2;
    const double kElementSizeMultiplier = 1.5;
    const double kElementXOffsetMultiplier = 0.3333333333;
    const double kElementYOffsetMultiplier = 0.2;
    const double kFontSizeMultiplier = 0.02;
    const double kXLocMultiplier = 0.3333333333;
    const double kYLocMultiplier = 0.1;
    const double kPauseScreenMessageX = 0.39285714285;
    const double kPauseScreenMessageY = 0.46428571428;
    const double kGameOverXPosMultiplier = 0.6;
    const double kGameOverYPosMultiplier = 0.16666666666;
    const double kGameOverSizeMultiplier = 0.14285714285;
    const double kPointsPerCoin = 0.1;
    
    const int kStartingLevel = 1;
    const int kPacmanStartingNumLives = 3;
    const int kPacmanLostNumLives = 0;
    const int kPointsPerLevelPassed = 100;
    const int kGhost1Index = 1;
    const int kGhost2Index = 2;
    const int kGhost3Index = 3;
    const int kGhost4Index = 4;
    const int kGhost5Index = 5;
    const int kNumGhostDirections = 4;
    const int kMaxNumScores = 10;
    const int kPacmanDiedWaitTime = 2;
    
    static const char kPauseButton = 'P';
    static const char kUpButton = 'W';
    static const char kDownButton = 'S';
    static const char kLeftButton = 'A';
    static const char kRightButton = 'D';
    
    const ofColor kStartScreenButtonColor{25,25,112};
    const ofColor kLeaderBoardStringColor{255,255,0};
    const ofColor kDefaultColor{255,255,255};
    const ofColor kLeaderboardScreenBackgroundColor{25,25,80};
    const ofColor kLeaderboardEndingButtonColor{0,0,0};
    
    // Class Variables that are used thorugh the game, ordered by type.
    GameState current_state;
    ofRectangle start_button;
    ofRectangle leaderboard_button;
    // Represents the current levels number.
    int level_num;
    std::vector<int> leaderboard;
    // The sounds that are used.
    ofSoundPlayer start_song;
    ofSoundPlayer pacman_siren;
    ofSoundPlayer waka_waka;
    ofSoundPlayer pacman_dying;
    ofSoundPlayer paused_sound;
    ofSoundPlayer leaderboard_song;
    ofSoundPlayer ending_song;
    Maze maze{kStartingLevel};
    Pacman pacman;
    // Each ghost is a different instance of the Ghost class.
    Ghost ghost_1{kGhost1Index};
    Ghost ghost_2{kGhost2Index};
    Ghost ghost_3{kGhost3Index};
    Ghost ghost_4{kGhost4Index};
    Ghost ghost_5{kGhost5Index};

    // Void functions that set up the variables, objects that the game uses.
    void setUpSounds();
    void setUpPositions();
    void setUpLeaderboardValues();
    void setUpButtonRectangles();
    
    // Makes sure that the waka waka sound is played only when pacman is moving.
    void updatePacmanSound();
    
    // Functions that are called through the game to update positions.
    void updatePacman();
    void updateGhosts();
    void updateGhostPosition(Ghost &ghost, int ghost_index);
    
    // The functions that are called at the end of a level
    // or at the end of the game.
    void updateLeaderboard();
    void loadNewLevel();

    // Functions that are called in the draw() function.
    void drawStartScreen();
    void drawPauseScreen();
    void drawGameState();
    void drawLeaderboard();
    void drawEndingScreen();
    
    // Returns the top 10 scores as a formatted string.
    std::string getLeaderboardMessage();
    
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
