// 
// created by Marie Toussaint on 12.08.2025
//

#include "Aliens.hpp"
#include "Constants.hpp"
#include "iostream"

Aliens::Aliens(sf::Vector2f position) :
    texture(),
    sprite(texture) {
        //load texture
        if(!
            texture.loadFromFile("assets/sprites/Spaceship.png"))
        throw std::invalid_argument("Could not load sprite");
        //set up sprite
        sprite.setTexture(texture);

        
    }
