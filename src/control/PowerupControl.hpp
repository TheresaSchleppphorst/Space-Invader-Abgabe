#ifndef POWERUPCONTROL_H
#define POWERUPCONTROL_H

#include <random>
#include <SFML/Graphics.hpp>

#include "../model/Powerup.hpp"
#include "../view/Layer.hpp"

class PowerupControl {
    public:
        //initialize control with layer
        PowerupControl(Layer &layer);

        void update_powerup(float elapsed_time);

        //draw powerup to the layer
        void draw_powerup();

        void new_powerup(float elapsed_time);
        

private:
        //Powerup object
        Powerup powerup;

        //layer on which the powerup is drawn
        Layer &layer;

        // random number generator
        std::mt19937 random_engine;

        // time between 3 and 6 seconds between new powerups
        std::uniform_real_distribution<float> time_between_powerup{5, 10}; // ÄNDERN

        // time until next shoot
        float nextPowerup_time = 0;

        // Tempo mit dem das Powerup nach unten kommt 
        float powerup_speed = 150; // ÄNDERN

        bool powerup_active = false;

        bool good_powerup = true;
};

#endif