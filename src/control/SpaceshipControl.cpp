#include "SpaceshipControl.hpp"
#include "../model/Constants.hpp"
#include "../model/Powerup.hpp"
#include <iostream>
#include <algorithm>

SpaceshipControl::SpaceshipControl(Layer &layer) : spaceship(), layer(layer), shoots(){}


void SpaceshipControl::update_spaceship(float elapsed_time){
    //horizontal position of the spaceship (will change with this function)
    float x = 0;
    //vertical position of the spaceship (the exact position where I want the spaceship to show)
    float y = spaceship.getPosition().y;
    //std::cout << "Der Wert der float-Variable ist: " << spaceship.getPosition().x << std::endl;
    if (spaceship.getPosition().x > constants::SPIELFELDRAND_LI && spaceship.getHorizontaleRichtung() == horizontaleRichtung::LEFT)
    { x = -200;
    }
    if (spaceship.getPosition().x < constants::SPIELFELDRAND_RE && spaceship.getHorizontaleRichtung() == horizontaleRichtung::RIGHT)
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
        for(auto& shoot: shoots){
            if(shoot.getActive()){
                layer.add_to_layer(shoot.getSprite());}
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
    auto spaceshipPosition = spaceship.getPosition();
    shoots.emplace_back(spaceshipPosition);
    auto& shoot = shoots.back();
    shoot.setPosition({spaceshipPosition.x -15 , spaceshipPosition.y -50});
    shoot.move_up();
}

void SpaceshipControl::update_shoot(float elapsed_time) {
    // check for powerups:

       if (powerup_active) {
        time_left -= elapsed_time;
        if (time_left <= 0) {
            powerup_active = false;
            time_left   = 0;
            speed = 400; // set speed to normal speed
        }
    }

    if(shoots.empty() == false){

    for(auto& shoot : shoots){
        float x = shoot.getPosition().x;
        float y = shoot.getPosition().y;

    if (shoot.getVertikaleRichtung() == vertikaleRichtung::UP) {
        y -= elapsed_time * speed;
        // update position
        shoot.setPosition({x, y});
    }}

    // Verschwinden der Schüsse:
    for (auto shootIterator = shoots.begin(); shootIterator != shoots.end(); ) {
       if (shootIterator->getSprite().getPosition().y >= constants::MITTE.y + 300) {
            shootIterator = shoots.erase(shootIterator);
       } else 
            shootIterator++;
    }}
}

void SpaceshipControl::activate_good_powerup(float time){
    if(powerup_active){return;}

    powerup_active = true;
    time_left = time;
    speed = 800; // shoots are faster
}

void SpaceshipControl::activate_bad_powerup(float time){
    if(powerup_active){return;}

    powerup_active = true;
    time_left = time;
    speed = 200; // shoots are slower
}
