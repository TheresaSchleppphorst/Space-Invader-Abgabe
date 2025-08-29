#ifndef SPACESHIPCONTROL_H
#define SPACESHIPCONTROL_H

#include <SFML/Graphics.hpp>
#include "../model/Spaceship.hpp"
//#include "ShootControl.hpp"
#include "../model/Shoot.hpp"
#include "../view/Layer.hpp"

class SpaceshipControl {
    public:
        //initialize control with layer
        SpaceshipControl(Layer &layer);

        //determine the position of the spaceship depending on the current movement
        void update_spaceship(float elapsed_time);

        //draw the spaceship to the layer
        void draw_spaceship();

        //draw the shoot to the layer
        void draw_shoot();

        //move the spaceship to the left
        void left_button_pressed();

        //move the spaceship to the right
        void right_button_pressed();

        //stop horizontal movement
        void direction_button_released(::horizontaleRichtung hR);

        //shoot
        void space_bar_pressed();

        //shoot movement
        void update_shoot(float elapsed_time);

private:
        //spaceship object
        Spaceship spaceship;

        //layer on which the spaceship is drawn
        Layer &layer; 

        // vector of all shoots
        std::vector<Shoot> shoots;

        // Bild für Shoot verwi
        sf::Texture shootTexture;

        friend class Game;
};

#endif

