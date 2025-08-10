#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../view/Layer.hpp"
#include "SpaceshipControl.hpp"
#include "OverlayControl.hpp"
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

    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;
    Layer overlay_layer;

    //Controls for different parts of the game
    SpaceshipControl spaceship_control;
    OverlayControl overlay_control;
};

#endif