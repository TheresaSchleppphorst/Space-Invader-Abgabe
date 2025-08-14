//
// Created by there on 05.08.2025.
//

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include <SFML/Graphics.hpp>

enum class horizontaleRichtung {
  LEFT,
  RIGHT,
  NONE
};

//Spaceship Class
class Spaceship{
  protected:
  
    //position of the spaceship
    sf::Vector2f position;
    //spaceship moves left or right
    horizontaleRichtung hR = horizontaleRichtung::NONE;

    sf:: Texture texture;
    sf::Sprite sprite;


public:
    //Initializes the spaceship
    Spaceship();
    //setter + getter Position
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    
    //check if spaceship is moving left or right
    horizontaleRichtung getHorizontaleRichtung() const;
    //spaceship is no longer moving to right or left
    void stop_horizontal_movement();
    //initiates movement to the right
    void move_right();
    //initiates movement to the left
    void move_left();
    //getter des Sprites
    const sf::Sprite &getSprite() const;


};

#endif //SPACESHIP_HPP
