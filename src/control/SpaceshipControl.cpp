#include "SpaceshipControl.hpp"
#include <iostream>

SpaceshipControl::SpaceshipControl(Layer &layer) : layer(layer){

}

void SpaceshipControl::update_spaceship(float elapsed_time){
    //horizontal position of the spaceship
    float x = 0;
    //vertical position of the spaceship STATIC
    float y = 50;
    //std::cout << "Der Wert der float-Variable ist: " << spaceship.getPosition().x << std::endl;
    if (spaceship.getPosition().x > 60 && spaceship.getHorizontaleRichtung() == horizontaleRichtung::LEFT)
    { x = -200;
    }
    if (spaceship.getPosition().x < 540 && spaceship.getHorizontaleRichtung() == horizontaleRichtung::RIGHT)
    { x = 200;
    }
    x = spaceship.getPosition().x + x * elapsed_time;

    //update position
    spaceship.setPosition({x, y});
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