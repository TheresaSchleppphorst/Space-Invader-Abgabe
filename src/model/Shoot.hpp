
#ifndef SHOOT_HPP
#define SHOOT_HPP
#include <SFML/Graphics.hpp>
#include "../view/Layer.hpp"

enum class vertikaleRichtung {
  UP,
  DOWN,
  NONE
};

class Shoot {
    protected:
    sf::Vector2f position;
    //shoot goes up or down (spaceship or alien)
    vertikaleRichtung vR = vertikaleRichtung::NONE;
    static sf::Texture texture;
    static sf::Texture alienTexture;
    sf::Sprite sprite;
    bool active = true;


  public:

    ~Shoot() = default;
    //constructor
    Shoot(sf::Vector2f position);
  
    
     //setter + getter Position
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    //check if movement is up or down
    vertikaleRichtung getVertikaleRichtung() const;
    //shot stops moving
    void stop_vertical_movement();
    //movement up
    void move_up();
    //movement down
    void move_down();
    
    //getter des Sprites
    const sf::Sprite &getSprite() const;

    // loading another image for the alien shots
    void setAlienShootSprite();

    // Activity Setter
    void setActive(bool status);
    // Activity Getter
    const bool getActive();
    // Changes the Active status of a Shot after an Colision to false
    void hit();


};

#endif //SHOOT_HPP
