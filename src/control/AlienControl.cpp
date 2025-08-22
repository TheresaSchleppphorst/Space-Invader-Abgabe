#include "AlienControl.hpp"
#include "../model/Aliens.hpp"
#include "../model/Constants.hpp"
#include <iostream>


AlienControl::AlienControl(Layer &layer) : layer(layer){
    AlienControl::build_Aliengrid();
}

void AlienControl::build_Aliengrid() {

    // Create the Alien grid.
    int level_depth = 5;

    // Creates an alien_grid depending on the required Level_depth.
    for (int i = 0; i < level_depth; i++){
        std::vector<Aliens> alien_row;
        float ifloat = static_cast<float>(i);

        // Fills the created alien_row with 11 Aliens each.
        for (int j = 0; j < 11; j++){
            float jfloat = static_cast<float>(j);
            Aliens newAlien = Aliens({72 + (24+15)*jfloat,-500 + (16+12)*ifloat});
            alien_row.push_back(newAlien);
        }

        // Adds the now filled alien_row to the alien_grid.
        alien_grid.push_back(alien_row);
    }
}

void AlienControl::update_aliens(float elapsed_time){
    // Incase theres need to alter the speed.
    float speedControl = 1.3;

    // the Grid moves right until the first alien hits the SPIELFELDRAND_RE,
    for(auto& row : alien_grid){
        for(auto& alien: row){

             // horrizontal position of the alien.
            float x = alien.getPosition().x;
            // vertical position of the alien.
            float y = alien.getPosition().y;

            if(((alien.getPosition().x > constants::SPIELFELDRAND_RE)||(alien.getPosition().x < constants::SPIELFELDRAND_LI))
            && !justMovedDown){
                    move_Aliengrid_down();
            }


            // Move alien depending on RichtungAlien.
            float movement = 12;
            if(alien.getRichtungAlien() == RichtungAlien::LEFT) {
                movement = - movement;
            }

            x = alien.getPosition().x + movement * elapsed_time * speedControl;

            //update position
            alien.setPosition({x, y});
        }
    }
    if(aliensInBounds()){
        justMovedDown = false;
    }
}

void AlienControl::draw_aliens(){
    // For every Row in the Alien Grid ...
    for(auto& row : alien_grid ) {
        // For every Alien in the Row ...
        for(auto& alien : row){
             layer.add_to_layer(alien.getSprite());
        }
    }
}

void AlienControl::draw_alien_shoot(){

    //TODO, wie oft sollen die Aliens schießen etc.

}

void AlienControl::move_Aliengrid_down() {

    for(auto& row : alien_grid){
        for(auto& alien : row){
            
            float y = alien.getPosition().y;
            float x = alien.getPosition().x;
            // testen ob + oder -:
            // (16+12) is an estimate can be change to our liking. Since all Aliens are moved down we dont need to consider spacing so much.
            alien.setPosition({x,y +(12)});
            // Switch Direction from left to right, or right to left:
            if(alien.getRichtungAlien() == RichtungAlien::RIGHT){
                alien.setRichtungAlien(RichtungAlien::LEFT);
        }
        else if(alien.getRichtungAlien() == RichtungAlien::LEFT){
                alien.setRichtungAlien(RichtungAlien::RIGHT);
            }
    }
}
justMovedDown = true;
}

bool AlienControl::aliensInBounds(){
    bool inBounds = true;

    for(auto& row : alien_grid){
        for(auto& alien : row){
            // checks if all aliens are in bounds, if they are not:
            // inBounds = false.
            if ((alien.getPosition().x > constants::SPIELFELDRAND_RE)||(alien.getPosition().x < constants::SPIELFELDRAND_LI)) {
                inBounds = false;
            }
        }
    }
    
    return inBounds;
}


