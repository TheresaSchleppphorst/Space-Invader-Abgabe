
#ifndef Powerup_HPP
#define Powerup_HPP
#include <SFML/Graphics.hpp>
#include "../view/Layer.hpp"
#include "../model/Shoot.hpp"


class Powerup {
    protected:
    sf::Vector2f position;
    vertikaleRichtung vR = vertikaleRichtung::NONE;
    sf:: Texture texture;
    sf::Sprite sprite;

  public:

    ~Powerup() = default;
    //constructor
    Powerup(sf::Vector2f position);

    //setter + getter Position
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    //check, if movement is up or down
    vertikaleRichtung getVertikaleRichtung() const;
    //powerup stops moving
    void stop_vertical_movement();
    //movement down
    void move_down();
    //getter of the sprite
    const sf::Sprite &getSprite() const;

    // change Sprite for bad PowerUps
    void setBadPowerupSprite();

    // change Sprite for good PowerUps
    void setGoodPowerupSprite();
};

#endif //Powerup_HPP
