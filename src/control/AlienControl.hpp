#ifndef ALIENCONTROL_H
#define ALIENCONTROL_H

#include <random>

#include <SFML/Graphics.hpp>
#include "../model/Aliens.hpp"
#include "../view/Layer.hpp"
#include "../model/Shoot.hpp"

class AlienControl {
    public:
        //initialize control with layer
        AlienControl(ILayer& layer);

        //create an Alien Grid starting at the given coordinates:
        void build_Aliengrid(int x, int y);

        //determine the position of the alien depending on the current movement
        void update_aliens(float elapsed_time);

        //draw the alien to the layer
        void draw_aliens();

        //draw the shoot to the layer
        void draw_shoot();

        // draw the alien shoot to the layer
        void draw_alien_shoot();

        // moves the Aliengrid down if outer bounds are reached.
        void move_Aliengrid_down();

        // checks if all aliens are with in the left and right Border:
        bool aliensInBounds();

        // checks if aliens have reached the bottom of the screen (invaded the Planet)
        // should lead to gameOver()
        bool bottomReached();

        // gives back the lowest row of aliens because only they can shoot
        std::vector<Aliens*> getAllAliens();

        // AlienGrid Getter:
        std::vector<std::vector<Aliens>> getAlienGrid();

        std::vector<std::vector<Aliens>>& getAlienGridRef();

        //JustMovedDown status Getter:
        bool getJustMovedDown();


        // random shooting -> sAlien is the current shooting Alien
        void alienShoot(Aliens* sAlien);

        void random_shoot(float elapsed_time);

        void update_shoot(float elapsed_time);

        void setMin(float nMin);

        void setMax(float nMax);

        void setSpeed(float nSpeed);

        void setSpeedControl(float nSpeed);

        //for testing purposes
        const std::vector<std::vector<Aliens>>& alienGrid() const { return alien_grid; }

        


private:
        //Alien Grid
        std::vector<std::vector<Aliens>> alien_grid;

        //Boolean used to controll the downward movement
        bool justMovedDown;

        // vector of all shoots
        std::vector<Shoot> shoots;

        // layer on which the aliens are drawn
        ILayer& layer; 

        // random number generator
        std::mt19937 random_engine;

        // Incase theres need to alter the speed of the alien grid.
        float speedControl = 4.0;

        // minimum and maximum amount of seconds inbetween shots
        float min= 2; // state.level einbinden !!
        float max = 3;

        float speed = 150;

        // time between min and max seconds inbetween the shoots of the aliens
        std::uniform_real_distribution<float> time_between_shoot{min, max};

        // time until next shoot
        float nextShoot_time = 0;
        
        friend class Game;
};

#endif

