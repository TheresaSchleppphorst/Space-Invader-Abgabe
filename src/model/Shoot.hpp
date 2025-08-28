
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
    //Schuss bewegt sich nach oben (Raumschiff) oder unten (Alien)
    vertikaleRichtung vR = vertikaleRichtung::NONE;
    static sf::Texture texture;
    sf::Sprite sprite;
    bool active = true;


  public:

    ~Shoot() = default;
    //Konstruktor
    Shoot(sf::Vector2f position);
  
    
     //setter + getter Position
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
    //check, ob Bewegung nach oben oder unten
    vertikaleRichtung getVertikaleRichtung() const;
    //Schuss bewegt sich nicht weiter
    void stop_vertical_movement();
    // Bewegung nach oben
    void move_up();
    // Bewegung nach oben
    void move_down();
    
    //getter des Sprites
    const sf::Sprite &getSprite() const;

    // anderes Bild für die Schüsse der Aliens laden
    void setAlienShootSprite();

    // Activity Setter
    void setActive(bool status);
    // Activity Getter
    const bool getActive();
    // Changes the Active status of a Shot after an Colision to false
    void hit();


};

#endif //SHOOT_HPP
