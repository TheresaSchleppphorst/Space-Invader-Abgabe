//
// Created by there on 07.08.2025.
//

#include "Spaceship.hpp"
#include "Constants.hpp"
#include "iostream"

Spaceship::Spaceship() :
    position({constants::MITTE_X_ACHSE, 50}),
    texture(),
    sprite(texture) {
          //load texture
          if(!
              texture.loadFromFile("assets/sprites/spriteSpaceship.png"))
            throw std::invalid_argument("Could not load sprite");
          //set up sprite
          sprite.setTexture(texture);
          sprite.setTextureRect(sf::IntRect({0,0}, {60,30}));
          sprite.setOrigin({50,100});
          sprite.setPosition(position);

    
}

void Spaceship::move_right(){
    if (hR != horizontaleRichtung::RIGHT)
    { hR = horizontaleRichtung::RIGHT;}
}

void Spaceship::move_left(){
    if (hR != horizontaleRichtung::LEFT)
    {hR = horizontaleRichtung::LEFT;}
}

void Spaceship::stop_horiontal_movement(){
    hR = horizontaleRichtung::NONE;
}

sf::Vector2f Spaceship::getPosition() const {
    return position;
}

int Spaceship::getAnzahlLeben() const {
    return anzahlLeben;
}

int Spaceship::getLevel() const {
    return level;
}

horizontaleRichtung Spaceship::getHorizontaleRichtung() const {
    return hR;
}

const sf::Sprite& Spaceship::getSprite() const {
    return sprite;
}

void Spaceship::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(position);
}

void Spaceship::setAnzahlLeben(int anzahlLeben){
    this->anzahlLeben = anzahlLeben;
}

void Spaceship:: setLevel(int level){
    this->level = level;
}

