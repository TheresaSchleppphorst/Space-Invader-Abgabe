
#include "Shoot.hpp"
#include "Constants.hpp"
#include "iostream"

Shoot::Shoot(sf::Vector2f position) :
    position({0,0}), // Position beim Aufrufen setzen, Je nachdem ob Alien oder Spaceship
    texture(),
    sprite(texture) {
          //load texture
          if(!
              texture.loadFromFile("assets/sprites/spriteShoot.png"))
            throw std::invalid_argument("Could not load sprite");
          //set up sprite
          sprite.setTexture(texture);
          sprite.setTextureRect(sf::IntRect({0,0}, {60,30}));
          sprite.setOrigin({50,100});
          sprite.setPosition(position);
}

void Shoot::move_up(){
    if (vR != vertikaleRichtung::UP)
    { vR = vertikaleRichtung::UP;}
}

void Shoot::move_down(){
    if (vR != vertikaleRichtung::DOWN)
    {vR = vertikaleRichtung::DOWN;}
}

// evt. unnögig:
void Shoot::stop_vertical_movement(){
    vR = vertikaleRichtung::NONE;
}

sf::Vector2f Shoot::getPosition() const {
    return position;
}

vertikaleRichtung Shoot::getVertikaleRichtung() const {
    return vR;
}

const sf::Sprite& Shoot::getSprite() const {
    return sprite;
}

void Shoot::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(position);
}