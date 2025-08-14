#include "SpaceshipControl.hpp"
#include <iostream>
#include "../model/Constants.hpp"

SpaceshipControl::SpaceshipControl(Layer &layer) : spaceship(), shoot(spaceship.getSprite().getPosition()), layer(layer){

}

void SpaceshipControl::update_spaceship(float elapsed_time){
    //horizontal position of the spaceship (will change with this function)
    float x = 0;
    //vertical position of the spaceship (the exact position where I want the spaceship to show)
    float y = spaceship.getPosition().y;
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

void SpaceshipControl::draw_shoot(){
    if (shoot_active){
        layer.add_to_layer(shoot.getSprite());
    }
}

void SpaceshipControl::right_button_pressed(){
    spaceship.move_right();
}

void SpaceshipControl::left_button_pressed(){
    spaceship.move_left();
}

void SpaceshipControl::direction_button_released(::horizontaleRichtung hR){
    if(hR == spaceship.getHorizontaleRichtung())
       spaceship.stop_horizontal_movement();
}

void SpaceshipControl::space_bar_pressed(){
    shoot_active = true;
    auto spaceshipPosition = spaceship.getPosition();
    shoot.setPosition({spaceshipPosition.x - 25, spaceshipPosition.y -20});
    shoot.move_up();

}


void SpaceshipControl::update_shoot(float elapsed_time) {
    if(shoot_active == true){

    float x = shoot.getPosition().x;
    float y = shoot.getPosition().y;
    float speed = 500.f;

    if (shoot.getVertikaleRichtung() == vertikaleRichtung::UP) {
        y -= elapsed_time * speed;
    }
 
    // update position
    shoot.setPosition({x, y});

    // NEU::
    const float top = -constants::VIEW_HEIGHT;
    const float halfH = shoot.getSprite().getOrigin().y;

    if (y + halfH < top) {
        shoot_active = false;
    }

}
}