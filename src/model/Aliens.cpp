
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
        sprite.setTextureRect(sf::IntRect({80, 365}, {constants::ALIEN_WIDTH, constants::ALIEN_HEIGHT}));
        sprite.setScale({0.08f, 0.08f});   
        sprite.setOrigin({constants::ALIEN_WIDTH / 2, constants::ALIEN_HEIGHT});        
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

void Aliens::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(position);
}

RichtungAlien Aliens::getRichtungAlien() const {
    return rA;
}

void Aliens::setRichtungAlien(RichtungAlien Richtung){
    rA = Richtung;
}

const sf::Sprite& Aliens::getSprite() const {
    return sprite;
}

void Aliens::setAlive(bool isAlive){
    alive = isAlive;
}

const bool Aliens::getAlive(){
    return alive;
}

void Aliens::take_damadge(){
    setAlive(false);
}
