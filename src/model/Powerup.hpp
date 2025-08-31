
#ifndef Powerup_HPP
#define Powerup_HPP
#include <SFML/Graphics.hpp>
#include "../view/Layer.hpp"
#include "../model/Shoot.hpp"


class Powerup {
    protected:
    sf::Vector2f position;
    //Schuss bewegt sich nach oben (Raumschiff) oder unten (Alien)
    vertikaleRichtung vR = vertikaleRichtung::NONE;
    sf:: Texture texture;
    sf::Sprite sprite;

  public:

    ~Powerup() = default;
    //Konstruktor
    Powerup(sf::Vector2f position);

    //setter + getter Position
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    //check, ob Bewegung nach oben oder unten
    vertikaleRichtung getVertikaleRichtung() const;
    //PowerUp bewegt sich nicht weiter
    void stop_vertical_movement();
    // Bewegung nach oben
    void move_down();
    //getter des Sprites
    const sf::Sprite &getSprite() const;

    // change Sprite for bad PowerUps
    void setBadPowerupSprite();

    // change Sprite for good PowerUps
    void setGoodPowerupSprite();
};

#endif //Powerup_HPP
