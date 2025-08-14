#ifndef OVERLAYCONTROL_H
#define OVERLAYCONTROL_H

#include <stddef.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Font.hpp>

#include "../view/Layer.hpp"

//Control for the overlay (score, game over text, level, lives)
class OverlayControl{
    public:
        //initializes the controller with the layer on which the score will be shown
        OverlayControl(Layer &layer);

        //if the spaceship shot an alien, the score is updated
        void update_score(size_t alien_hit);

        //the level of the player (spaceship)
        void update_level(size_t level);

        //the remaining number of lives of the player (spaceship)
        void update_lives(int lives);

        //draw the overlay to the layer
        void draw();

        //show the game-over-text
        void game_over();

    private:
        //Text font
        sf:: Font font;

        //score
        size_t score = 0;

        //lives 
        int lives = 3;

        //level
        size_t level = 0;

        //Text element showing the score
        sf::Text score_view;

        ///Text element showing the level
        sf::Text level_view;

        ///Text element showing the lives
        sf::Text lives_view;

        //layout of the header
        void layout_header();

        //Text element showing in the middle of the screen
        sf::Text center_view;

        //indicator if the text in the middle of the screen is shown
        bool show_center_view = false;

        //layer on which the text is drawn
        Layer &layer;


};

#endif