#ifndef SPACESHIPCONTROL_H
#define SPACESHIPCONTROL_H

#include <SFML/Graphics.hpp>

#include "../model/Spaceship.hpp"
//#include "ShootControl.hpp"
//#include "../model/Shoot.hpp"
#include "../view/Layer.hpp"

class SpaceshipControl {
    public:
        //initialize control with layer
        SpaceshipControl(Layer &layer);

        //determine the position of the spaceship depending on the current movement
        void update_spaceship(float elapsed_time);

        //draw the spaceship to the layer
        void draw_spaceship();

        //move the spaceship to the left
        void left_button_pressed();

        //move the spaceship to the right
        void right_button_pressed();

        //stop horizontal movement
        void direction_button_released(::horizontaleRichtung hR);

private:
        //spaceship object
        Spaceship spaceship;

        //layer on which the spaceship is drawn
        Layer &layer;    
};

#endif

