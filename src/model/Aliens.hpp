

#ifndef ALIENS_HPP
#define ALIENS_HPP

#include <SFML/Graphics.hpp>

<<<<<<< HEAD
// Enum um festzulegen um welche Kategorie Alien es sich handelt.
enum class schwierigkeit {
  EINFACH,
  MITTEL,
  SCHWER,
  BOSS
};


//Alien Class 
class Aliens {
  private:
  // Anzahl der restlichen Leben
    int anzahlLeben;
  // Position des Aliens
=======

enum class RichtungAlien {
  LEFT,
  RIGHT,
};

class Aliens {

  protected:
>>>>>>> origin/main
    sf::Vector2f position;

    sf::Texture texture;
    sf::Sprite sprite;
<<<<<<< HEAD

  public:
    //Konstruktor
    Aliens(sf::Vector2f position, schwierigkeit);
    //virtual Destruktor
    virtual ~Aliens();
    // Setter und Getter der Leben:
    int getAnzahlLeben() const;
    void setAnzahlLeben(int leben);
    // Bewegungsfunktionen
    void bewegenR(); //Bewegung Rechts
    void bewegenL(); //Bewegung Links
    

=======

    //determines if the alien is shown (alive = true) or not 
    bool alive;

    //alien formation starts at the left hand side and moves to the right 
    RichtungAlien rA = RichtungAlien::RIGHT;


  public:
    //Konstruktor
    Aliens();
    
    //setter + getter position 
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f position);
   
    //check if spaceship is moving left or right
    RichtungAlien getRichtungAlien() const;
    
    //initiates movement to the right
    void move_right();
    //initiates movement to the left
    void move_left();
    
    //getter des Sprites
    const sf::Sprite &getSprite() const;


};
>>>>>>> origin/main




};
#endif ALIENS_HPP