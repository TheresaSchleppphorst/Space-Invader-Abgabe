
#include "Aliens.hpp"
#include "Constants.hpp"
#include "iostream"

sf::Texture Aliens::texture;

Aliens::Aliens(sf::Vector2f alienPos) :
    
    position(alienPos),
    sprite(texture) {
        //load texture
        if(!
            texture.loadFromFile("assets/sprites/spritesheetCOLOR.png")) //b: 962px h:965px
        throw std::invalid_argument("Could not load sprite");
        //set up sprite
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect({0, 321}, {481, 321}));
        sprite.setScale({0.08f, 0.08f});
        sf::FloatRect bounds = sprite.getGlobalBounds();     
        sprite.setOrigin({bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y });        
        sprite.setPosition(alienPos);
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
