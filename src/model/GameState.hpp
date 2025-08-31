#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GamePhase {playing, levelCleared, gameOver};

//globally accessible variables that represent the states
struct GameState {
    GamePhase phase = GamePhase::playing;
    int lives = 3;
    int score = 0;
    int level = 1;
    int alien_hits = 0;
    int spaceship_hits = 0;
};

#endif