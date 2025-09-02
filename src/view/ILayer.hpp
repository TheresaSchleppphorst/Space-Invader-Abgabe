#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

// Interface class, needed for the test

class ILayer {
public:
    virtual ~ILayer() = default;
    
    // adds the drawable element to the layer
    virtual void add_to_layer(const sf::Drawable &drawable) = 0;

    // draws the scene to the window
    virtual void draw() = 0;

    // clear the layer, remove all drawable elements
    virtual void clear() = 0;

    // adjust the layer's view
    virtual void set_view(const sf::View &view) = 0;
};