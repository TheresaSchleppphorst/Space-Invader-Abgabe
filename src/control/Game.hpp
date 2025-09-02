#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../view/ILayer.hpp"
#include "SpaceshipControl.hpp"
#include "OverlayControl.hpp"
#include "AlienControl.hpp"
#include "PowerupControl.hpp"
#include "../model/GameState.hpp"


// Game class
class Game {

public:
    //initialize the game (window and controls)
    Game();

    // start the game
    void start();

private:
    //the state of all variables (level, lives etc.)
    GameState state;

    //phase of the game
    GamePhase phase = GamePhase::playing;

    //starts the new level
    void start_next_level();

    //resets the game after game over
    void reset_game();

    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    //Collision Functions:
    bool collisionAlien();
    bool collisionSpaceship();
    bool collisionPowerup();

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;
    Layer overlay_layer;

    //Controls for different parts of the game
    SpaceshipControl spaceship_control;
    OverlayControl overlay_control;
    AlienControl alien_control;
    PowerupControl powerup_control;
};

#endif