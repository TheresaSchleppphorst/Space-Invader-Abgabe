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
        void build_Aliengrid();

        //determine the position of the alien depending on the current movement
        void update_aliens(float elapsed_time);

        //draw the alien to the layer
        void draw_aliens();

        // draw the alien shoot to the layer
        void draw_alien_shoot();

        // moves the Aliengrid down if outer bounds are reached.
        void move_Aliengrid_down();

        // checks if all aliens are with in the left and right Border:
        bool aliensInBounds();

        // checks if aliens have reached the bottom of the screen (invaded the Planet)
        // should lead to gameOver()
        bool bottomReached();
private:
        //Alien Grid
        std::vector<std::vector<Aliens>> alien_grid;

        //Boolean used to controll the downward movement
        bool justMovedDown;

        //layer on which the alien is drawn
        Layer &layer; 
        
       friend class Game;
};

#endif

