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

        // getter for speed
        float getSpeed();


        // setter for speed
        void setSpeed(float newSpeed);

        //shoot movement
        void update_shoot(float elapsed_time);

        // activation of powerup for time seconds
        void activate_good_powerup(float time);

        // activation of powerup for time seconds
        void activate_bad_powerup(float time);

        //for testing purposes
        const Spaceship& getSpaceship() const { return spaceship; }

        //shoots and powerups disappear
        void clearAll();


private:
        //spaceship object
        Spaceship spaceship;

        //layer on which the spaceship is drawn
        Layer &layer; 

        // speed of shoots
        float speed = 300;

        // vector of all shoots
        std::vector<Shoot> shoots;

        sf::Texture shootTexture;

        friend class Game;

        // true if powerup is currently active
        bool powerup_active = false;

        // how long the powerup is still active
        float time_left = 0;

        // necessary to set speed back to normal speed after a powerup
        bool good = false;
        bool bad = false;
};

#endif

