#ifndef GAMESTATE_H
#define GAMESTATE_H

//globally accessible variables that represent the states
struct GameState {
    int lives = 3;
    int score = 0;
    int level = 1;
    int alien_hits = 0;
    int spaceship_hits = 0;
    bool game_won = false;
};

#endif