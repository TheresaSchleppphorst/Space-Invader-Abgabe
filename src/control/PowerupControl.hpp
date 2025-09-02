#ifndef POWERUPCONTROL_H
#define POWERUPCONTROL_H

#include <random>
#include <SFML/Graphics.hpp>

#include "../model/Powerup.hpp"
#include "../view/ILayer.hpp"

class PowerupControl {
    public:
        //initialize control with layer
        PowerupControl(ILayer& layer);

        void update_powerup(float elapsed_time);

        //draw powerup to the layer
        void draw_powerup();

        void new_powerup(float elapsed_time);

        bool get_powerup_active();

        bool get_good_powerup();

        void delete_powerup();
        

private:
        //Powerup object
        Powerup powerup;

        //layer on which the powerup is drawn
        ILayer& layer;

        // random number generator
        std::mt19937 random_engine;

        // time between 3 and 6 seconds between new powerups
        std::uniform_real_distribution<float> time_between_powerup{5, 10}; // ÄNDERN

        // time until next shoot
        float nextPowerup_time = 0;

        // Tempo mit dem das Powerup nach unten kommt 
        float powerup_speed = 150; 

        bool powerup_active = false;

        bool good_powerup = true;

        friend class Game;
};

#endif