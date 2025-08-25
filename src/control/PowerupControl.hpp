#ifndef POWERUPCONTROL_H
#define POWERUPCONTROL_H

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
        

private:
        //Powerup object
        Powerup powerup;

        //layer on which the powerup is drawn
        Layer &layer;

};

#endif