#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "../src/control/PowerupControl.hpp"
#include "../src/model/Constants.hpp"
#include "../src/view/Layer.hpp"


class PowerupControlTest : public ::testing::Test{

    public:
        PowerupControlTest()
        : window(sf::VideoMode(1,1,32), "test", sf::Style::None)
        , layer(window)
        , pc(layer)
        {
            window.setVisible(false);
        }

    protected:
        sf::RenderWindow window;
        Layer layer;
        PowerupControl pc;
};

TEST_F(PowerupControlTest, name){
    SUCCEED();
}