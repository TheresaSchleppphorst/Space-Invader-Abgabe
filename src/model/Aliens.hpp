

#ifndef ALIENS_HPP
#define ALIENS_HPP

#include <SFML/Graphics.hpp>

enum class RichtungAlien {
  LEFT,
  RIGHT,
};

class Aliens {

  protected:

    sf::Vector2f position;

    static sf::Texture texture;
    sf::Sprite sprite;

    //determines if the alien is shown (alive = true) or not 
    bool alive = true;

    //alien formation starts at the left hand side and moves to the right 
    RichtungAlien rA = RichtungAlien::RIGHT;


  public:
    //constructor
    Aliens(sf::Vector2f alienPos);
    
    //setter + getter position 
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
   
    //check if alien is moving left or right
    RichtungAlien getRichtungAlien() const;
    //set RichtungAlien
    void setRichtungAlien(RichtungAlien Richtung);
    
    //initiates movement to the right
    void move_right();
    //initiates movement to the left
    void move_left();
    
    //Sprite getter
    const sf::Sprite &getSprite() const;

    //alive Status getter
    const bool getAlive();

    //alive Status setter
    void setAlive(bool isAlive);

    //Damadge funktion:
    void take_damadge();


};

#endif 