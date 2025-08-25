#include "AlienControl.hpp"
#include "OverlayControl.hpp"
#include "../model/Aliens.hpp"
#include "../model/Constants.hpp"
#include <iostream>


AlienControl::AlienControl(Layer &layer) : layer(layer){
    AlienControl::build_Aliengrid();
}

void AlienControl::build_Aliengrid() {

    // Create the Alien grid.
    int level_depth = 5;

    // set Variables:
    // 0.08 = texture scale.
    float alien_gap_H = constants::ALIEN_WIDTH * 0.08 /2;
    float alien_gap_V = constants::ALIEN_HEIGHT * 0.08 /2;

    // accounting for the AlienSprite Origin:
    float sprite_gap_H = constants::ALIEN_WIDTH * 0.08;
    float sprite_gap_V = constants::ALIEN_HEIGHT * 0.08;
    

    // Creates an alien_grid depending on the required Level_depth.
    for (int i = 0; i < level_depth; i++){
        std::vector<Aliens> alien_row;
        float ifloat = static_cast<float>(i);

        // Fills the created alien_row with 11 Aliens each.
        for (int j = 0; j < 11; j++){
            float jfloat = static_cast<float>(j);
            Aliens newAlien = Aliens({60 + (alien_gap_H + sprite_gap_H)*jfloat,-450 + (alien_gap_V + sprite_gap_V)*ifloat});
            alien_row.push_back(newAlien);
        }

        // Adds the now filled alien_row to the alien_grid.
        alien_grid.push_back(alien_row);
    }
}

void AlienControl::update_aliens(float elapsed_time){
    // Problem with the communication between AlienControl and Game, since Game controlls the game_over() function.
    

    // Incase theres need to alter the speed.
    float speedControl = 4.0;

    if(!aliensInBounds() && !justMovedDown){
                    move_Aliengrid_down();
            }

    // the Grid moves right until the first alien hits the SPIELFELDRAND_RE,
    for(auto& row : alien_grid){
        for(auto& alien: row){

             // horrizontal position of the alien.
            float x = alien.getPosition().x;
            // vertical position of the alien.
            float y = alien.getPosition().y;

            // Move alien depending on RichtungAlien.
            float movement = 12;
            if(alien.getRichtungAlien() == RichtungAlien::LEFT) {
                movement = - movement;
            }

            x = alien.getPosition().x + movement * elapsed_time * speedControl;

            //update position
            y = alien.getPosition().y;
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

    //TODO

}

void AlienControl::move_Aliengrid_down() {

    for(auto& row : alien_grid){
        for(auto& alien : row){
            
            float y = alien.getPosition().y;
            float x = alien.getPosition().x;
        
            // (16+12) is an estimate can be change to our liking. Since all Aliens are moved down we dont need to consider spacing.

            alien.setPosition({x,y + (12)});
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

        if(row.front().getPosition().x < constants::SPIELFELDRAND_LI || row.back().getPosition().x > constants::SPIELFELDRAND_RE) {

            inBounds = false;
    }
}
 return inBounds;
}

// checks if the bottom boundry has been breached.
bool AlienControl::bottomReached(){

    bool reached = false;
    for(auto& row : alien_grid){
        for(auto& alien : row){
            if (alien.getPosition().y >= constants::SPIELFELDRAND_UN){
                reached = true;
            }
        }
    }
    
return reached;

}