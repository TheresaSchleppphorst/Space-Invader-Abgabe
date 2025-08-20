#include "AlienControl.hpp"
#include <iostream>

AlienControl::AlienControl(Layer &layer) : layer(layer){

}

void AlienControl::update_aliens(float elapsed_time){

    //TODO
}

void AlienControl::draw_aliens(){
    layer.add_to_layer(alien.getSprite());
}


