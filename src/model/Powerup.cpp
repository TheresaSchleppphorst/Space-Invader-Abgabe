
#include "Powerup.hpp"
#include "Constants.hpp"
#include "iostream"

Powerup::Powerup(sf::Vector2f position) :
    position(position), // Position beim Aufrufen setzen, je nachdem wo sich Alien oder Spaceship befinden
    texture(),
    sprite(texture) {
          //load texture
          if(!
              texture.loadFromFile("assets/sprites/spriteGoodPowerUp.png"))
            throw std::invalid_argument("Could not load sprite");
          //set up sprite
          sprite.setTexture(texture);
          sprite.setTextureRect(sf::IntRect({0,0}, {100,100}));
          sprite.setOrigin({30.f, 15.f});
          sprite.setScale(sf::Vector2f{0.9, 0.9});
          sprite.setPosition(position);
}


void Powerup::move_down(){
    if (vR != vertikaleRichtung::DOWN)
    {vR = vertikaleRichtung::DOWN;}
}

// evt. unnögig:
void Powerup::stop_vertical_movement(){
    vR = vertikaleRichtung::NONE;
}

sf::Vector2f Powerup::getPosition() const {
    return position;
}

vertikaleRichtung Powerup::getVertikaleRichtung() const {
    return vR;
}

const sf::Sprite& Powerup::getSprite() const {
    return sprite;
}

void Powerup::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(position);
}

void Powerup::setBadPowerupSprite()
{
    if (!texture.loadFromFile("assets/sprites/spriteBadPowerUp.png")) {
        throw std::invalid_argument("Could not load sprite");
    }
    sprite.setTexture(texture);
          sprite.setTextureRect(sf::IntRect({0,0}, {100, 100}));
          sprite.setOrigin({30.f, 15.f});
          sprite.setScale(sf::Vector2f{0.8, 0.8});
          sprite.setPosition(position);
}

void Powerup::setGoodPowerupSprite()
{
    if (!texture.loadFromFile("assets/sprites/spriteGoodPowerUp.png")) {
        throw std::invalid_argument("Could not load sprite");
    }
    sprite.setTexture(texture);
          sprite.setTextureRect(sf::IntRect({0,0}, {100, 100}));
          sprite.setOrigin({30.f, 15.f});
          sprite.setScale(sf::Vector2f{0.8, 0.8});
          sprite.setPosition(position);
}
