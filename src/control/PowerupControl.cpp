#include "PowerupControl.hpp"


PowerupControl::PowerupControl(Layer &layer) : powerup(sf::Vector2f{0, 0}), layer(layer){}

void PowerupControl::update_powerup(float elapsed_time){

    (void)elapsed_time; // später entfernen

}


void PowerupControl::draw_powerup(){
    layer.add_to_layer(powerup.getSprite());
}
