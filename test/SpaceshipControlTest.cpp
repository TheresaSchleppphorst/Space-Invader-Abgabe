#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

#include "../src/control/SpaceshipControl.hpp"
#include "../src/model/Constants.hpp"
#include "../src/view/Layer.hpp"

class SpaceshipControlTest : public ::testing::Test {

public:
   SpaceshipControlTest()
    : window(sf::VideoMode(1, 1, 32), "test", sf::Style::None)  
    , layer(window)
    , s(layer)
{
    window.setVisible(false); 
}


protected:
    sf::RenderWindow window;
    Layer            layer;
    SpaceshipControl s;
};

//x value increases while y stays stable
TEST_F(SpaceshipControlTest, RightButtonPressed) {
    auto start = s.getSpaceship().getPosition();
    s.right_button_pressed();
    s.update_spaceship(1.0f);
    auto end = s.getSpaceship().getPosition();

    EXPECT_GT(end.x, start.x);
    EXPECT_FLOAT_EQ(end.y, start.y);
}

//x value decreases while y stays stable
TEST_F(SpaceshipControlTest, LeftButtonPressed) {
    auto start = s.getSpaceship().getPosition();
    s.left_button_pressed();
    s.update_spaceship(1.0f);
    auto end = s.getSpaceship().getPosition();

    EXPECT_LT(end.x, start.x);
    EXPECT_FLOAT_EQ(end.y, start.y);
}

//releasing a direction button stops the movement 
TEST_F(SpaceshipControlTest, DirectionButtonReleased) {
    s.right_button_pressed();
    s.update_spaceship(0.5f); 
    const auto mid = s.getSpaceship().getPosition();

    s.direction_button_released(horizontaleRichtung::RIGHT);
    s.update_spaceship(1.0f); 
    const auto end = s.getSpaceship().getPosition();

    EXPECT_FLOAT_EQ(end.x, mid.x);
    EXPECT_FLOAT_EQ(end.y, mid.y);
}

//nothing moves if I don't press a button
TEST_F(SpaceshipControlTest, NoMovementWithoutButton) {
    const auto start = s.getSpaceship().getPosition();
    s.update_spaceship(1.0f);
    const auto end = s.getSpaceship().getPosition();

    EXPECT_FLOAT_EQ(end.x, start.x);
    EXPECT_FLOAT_EQ(end.y, start.y);
}

//we play in boundaries
TEST_F(SpaceshipControlTest, RespectBoundaries) {
    //left boundary
    s.getSpaceship().setPosition({constants::SPIELFELDRAND_LI, s.getSpaceship().getPosition().y});
    s.left_button_pressed();
    s.update_spaceship(1.0f);

    const auto pos = s.getSpaceship().getPosition();
    EXPECT_GE(pos.x, constants::SPIELFELDRAND_LI);

    //right boundary
    s.getSpaceship().setPosition({constants::SPIELFELDRAND_RE, s.getSpaceship().getPosition().y});
    s.right_button_pressed();
    s.update_spaceship(1.0f);

    const auto pos = s.getSpaceship().getPosition();
    EXPECT_LE(pos.x, constants::SPIELFELDRAND_RE);
}



