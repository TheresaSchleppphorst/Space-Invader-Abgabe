#ifndef MOCKLAYER_H
#define MOCKLAYER_H

#include "ILayer.hpp"
#include <gmock/gmock.h>


//
class MockLayer : public ILayer {
public:

    MOCK_METHOD(void, add_to_layer, (const sf::Drawable &drawable), (override));
    
    MOCK_METHOD(void, draw, (), (override));

    MOCK_METHOD(void, clear, (), (override));

    MOCK_METHOD(void, set_view, (const sf::View &view), (override));

};

#endif