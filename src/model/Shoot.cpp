
#include "Shoot.hpp"
#include "Constants.hpp"
#include "iostream"

sf::Texture Shoot::texture;
sf::Texture Shoot::alienTexture;

Shoot::Shoot(sf::Vector2f position) :
    position(position), // Position beim Aufrufen setzen, je nachdem wo sich Alien oder Spaceship befinden
    sprite(texture) {
          //load texture
          if(!
              texture.loadFromFile("assets/sprites/spriteShoot.png"))
            throw std::invalid_argument("Could not load sprite");
          //set up sprite
          sprite.setTexture(texture);
          sprite.setTextureRect(sf::IntRect({0,0}, {110,180}));
          sprite.setOrigin({30.f, 15.f});
          sprite.setScale(sf::Vector2f{0.18f, 0.18f});
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

void Shoot::setAlienShootSprite()
{
    if (!alienTexture.loadFromFile("assets/sprites/spriteAlienShoot.png")) {
        throw std::invalid_argument("Could not load sprite");
    }

    sprite.setTexture(alienTexture);
          sprite.setTextureRect(sf::IntRect({0,0}, {1216, 1216}));
          sprite.setOrigin({30.f, 15.f});
          sprite.setScale(sf::Vector2f{0.04, 0.04});
          sprite.setPosition(position);
}

void Shoot::setActive(bool status){
    active = status;
}
    
const bool Shoot::getActive(){
    return active;
}

void Shoot::hit(){
    setActive(false);
}
