//
// Created by there on 05.08.2025.
//

#ifndef ALIENS_HPP
#define ALIENS_HPP

#include <SFML/Graphics.hpp>

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
    sf::Vector2f position;

    sf::Texture texture;
    sf::Sprite sprite;

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
    





};
#endif ALIENS_HPP