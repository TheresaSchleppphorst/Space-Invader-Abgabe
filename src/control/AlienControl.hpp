#ifndef ALIENCONTROL_H
#define ALIENCONTROL_H

#include <SFML/Graphics.hpp>

#include "../model/Aliens.hpp"
//#include "ShootControl.hpp"
//#include "../model/Shoot.hpp"
#include "../view/Layer.hpp"

class AlienControl {
    public:
        //initialize control with layer
        AlienControl(Layer &layer);

        //determine the position of the alien depending on the current movement
        void update_aliens(float elapsed_time);

        //draw the alien to the layer
        void draw_aliens();

private:
        //alien object
        Aliens alien;

        //layer on which the alien is drawn
        Layer &layer;    
};

#endif

