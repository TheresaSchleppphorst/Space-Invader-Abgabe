#ifndef POWERUPCONTROL_H
#define POWERUPCONTROL_H

#include <random>
#include <SFML/Graphics.hpp>

#include "../model/Powerup.hpp"
#include "../view/ILayer.hpp"
#include "../control/SpaceshipControl.hpp"

class PowerupControl {
    public:
        //initialize control with layer
        PowerupControl(ILayer& layer);

        //updates the powerup
        void update_powerup(float elapsed_time);

        //draw powerup to the layer
        void draw_powerup();

        //creates a new powerup
        void new_powerup(float elapsed_time);

        //getter + setter
        bool get_powerup_active();
        void set_powerup_active(bool value) {powerup_active = value;};

        //if its true its a good powerup
        bool get_good_powerup();
        //void set_good_powerup (bool b) {good_powerup = b;};

        //sets the boolean active = false
        void delete_powerup(SpaceshipControl& sc);

        //getter + setter
        float getNextPowerupTime() {return nextPowerup_time;} 
        void setNextPowerupTime(float time) {nextPowerup_time = time;};

        //for testing purposes
        Powerup getPowerup() {return powerup;};
        
        

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

        // speed of the power up
        float powerup_speed = 150; 

        //default is false, so powerup not active
        bool powerup_active = false;

        //default is true, so powerup is good
        bool good_powerup = true;

        friend class Game;
};

#endif