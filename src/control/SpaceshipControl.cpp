#include "SpaceshipControl.hpp"

SpaceshipControl::SpaceshipControl(Layer &layer) : layer(layer){

}

void SpaceshipControl::draw_spaceship(){
    layer.add_to_layer(spaceship.getSprite());
}

void SpaceshipControl::right_button_pressed(){
    spaceship.move_right();
}

void SpaceshipControl::left_button_pressed(){
    spaceship.move_left();
}

void SpaceshipControl::direction_button_released(::horizontaleRichtung hR){
    if(hR == spaceship.getHorizontaleRichtung())
       spaceship.stop_horiontal_movement();
}