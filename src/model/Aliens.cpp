
#include "Aliens.hpp"
#include "Constants.hpp"
#include "iostream"

Aliens::Aliens() :
    position({constants::MITTE_X_ACHSE, -10}),
    texture(),
    sprite(texture) {
        //load texture
        if(!
            texture.loadFromFile("assets/sprites/spritesheetCOLOR.png")) //b: 962px h:965px
        throw std::invalid_argument("Could not load sprite");
        //set up sprite
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect({0, 321}, {481, 321}));
        sprite.setScale({0.15, 0.15});
        sf::FloatRect bounds = sprite.getGlobalBounds();     
        sprite.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y });        
        sprite.setPosition({20, -500});
}
 

void Aliens::move_right(){
    if (rA != RichtungAlien::RIGHT)
    { rA = RichtungAlien::RIGHT;}
}

void Aliens::move_left(){
    if (rA != RichtungAlien::LEFT)
    {rA = RichtungAlien::LEFT;}
}

sf::Vector2f Aliens::getPosition() const {
    return position;
}


RichtungAlien Aliens::getRichtungAlien() const {
    return rA;
}

const sf::Sprite& Aliens::getSprite() const {
    return sprite;
}

void Aliens::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(position);
}
