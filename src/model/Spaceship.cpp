//
// Created by there on 07.08.2025.
//

#include "Spaceship.hpp"
#include "Constants.hpp"
#include "iostream"

Spaceship::Spaceship() :
    position({constants::MITTE_X_ACHSE, 0}),
    texture(),
    sprite(texture) {
          //load texture
          if(!
              texture.loadFromFile("assets/sprites/pixilart-drawing.png"))
            throw std::invalid_argument("Could not load sprite");
          //set up sprite
          sprite.setTexture(texture, true);
          //sprite.setTextureRect(sf::IntRect({0,0}, {80,60}));
          //sprite.setOrigin({80,60});
          auto g = sprite.getLocalBounds();
    
          std::cout << "Sprite @ (" << g.position.x << "," << g.position.y << ") size (" << g.size.x << "x" << g.size.y << ")" << std::endl;

          //float horizontaleMitteDesSprites = (bounds.size.x / 2);
          //sprite.setOrigin({horizontaleMitteDesSprites, bounds.size.y});       
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

