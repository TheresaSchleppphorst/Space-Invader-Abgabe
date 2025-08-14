#include "SpaceshipControl.hpp"

SpaceshipControl::SpaceshipControl(Layer &layer) : spaceship(), shoot(spaceship.getSprite().getPosition()), layer(layer){

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
       spaceship.stop_horiontal_movement();
}

void SpaceshipControl::space_bar_pressed(){
    shoot_active = true;
    auto spaceshipPosition = spaceship.getPosition();
    shoot.setPosition({spaceshipPosition.x, spaceshipPosition.y -20});
    shoot.move_up();

}

void SpaceshipControl::update_spaceship(float elapsed_time) {
    (void)elapsed_time;
}


void SpaceshipControl::update_shoot(float elapsed_time) {
    if(shoot_active == true){

    float x = shoot.getPosition().x;
    float y = shoot.getPosition().y;
    float speed = 50;

    if (shoot.getVertikaleRichtung() == vertikaleRichtung::UP) {
        y -= elapsed_time * speed;
    }
 
    // update position
    shoot.setPosition({x, y});

    if (y < 0.f) {
        shoot_active = false;
    }

}
}