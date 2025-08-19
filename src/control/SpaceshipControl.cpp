#include "SpaceshipControl.hpp"
#include <iostream>
#include "../model/Constants.hpp"
#include <algorithm>

SpaceshipControl::SpaceshipControl(Layer &layer) : spaceship(), layer(layer), shoots(){}


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
        for(const auto& shoot: shoots){
        layer.add_to_layer(shoot.getSprite());}
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
    shoot.setPosition({spaceshipPosition.x - 25, spaceshipPosition.y -20});
    shoot.move_up();
}

void SpaceshipControl::update_shoot(float elapsed_time) {
    if(shoots.empty() == false){

    float speed = 500.f;

    for(auto& shoot : shoots){
        float x = shoot.getPosition().x;
        float y = shoot.getPosition().y;

    if (shoot.getVertikaleRichtung() == vertikaleRichtung::UP) {
        y -= elapsed_time * speed;
        // update position
        shoot.setPosition({x, y});
    }
    }

    // Verschwinden der Schüsse:
    
    for (auto shootIterator = shoots.begin(); shootIterator != shoots.end(); ) {
       if (shootIterator->getSprite().getPosition().y >= constants::MITTE.y + 300) {
            shootIterator = shoots.erase(shootIterator);
        } else 
            shootIterator++;
    }
    }
}
