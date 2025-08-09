//
// Created by there on 05.08.2025.
//

#ifndef ALIENS_HPP
#define ALIENS_HPP

#include <SFML/Graphics.hpp>

class Aliens {
  private:
    sf::Vector2f position;


  public:
    //Konstruktor
    Aliens(sf::Vector2f position);
    //virtual Destruktor
    virtual ~Aliens();

}

#endif //ALIENS_HPP
