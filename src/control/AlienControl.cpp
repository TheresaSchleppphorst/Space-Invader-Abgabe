#include "AlienControl.hpp"
#include "../model/Aliens.hpp"
#include <iostream>

AlienControl::AlienControl(Layer &layer) : layer(layer){
    AlienControl::build_AlienGrid();
}

void AlienControl::build_AlienGrid() {

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

    //TODO finish the Update function

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


