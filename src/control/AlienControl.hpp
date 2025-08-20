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

        //create an Alien Grid:
        void build_AlienGrid();

        //determine the position of the alien depending on the current movement
        void update_aliens(float elapsed_time);

        //draw the alien to the layer
        void draw_aliens();

        // draw the alien shoot to the layer
        void draw_alien_shoot();

private:
        // Alien Grid
        std::vector<std::vector<Aliens>> alien_grid;

        //layer on which the alien is drawn
        Layer &layer; 
        
       
};

#endif

