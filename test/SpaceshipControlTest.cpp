#include <gtest/gtest.h>
#include "../src/view/MockLayer.hpp"

#include "../src/control/SpaceshipControl.hpp"
#include "../src/model/Constants.hpp"


class SpaceshipControlTest : public ::testing::Test {

public:
 SpaceshipControlTest() : sc(layer) {}


protected:
    MockLayer layer;
    SpaceshipControl sc;
};

//x value increases while y stays stable
TEST_F(SpaceshipControlTest, RightButtonPressed) {
    auto start = sc.getSpaceship().getPosition();
    sc.right_button_pressed();
    sc.update_spaceship(1.0f);
    auto end = sc.getSpaceship().getPosition();

    EXPECT_GT(end.x, start.x);
    EXPECT_FLOAT_EQ(end.y, start.y);
}

//x value decreases while y stays stable
TEST_F(SpaceshipControlTest, LeftButtonPressed) {
    auto start = sc.getSpaceship().getPosition();
    sc.left_button_pressed();
    sc.update_spaceship(1.0f);
    auto end = sc.getSpaceship().getPosition();

    EXPECT_LT(end.x, start.x);
    EXPECT_FLOAT_EQ(end.y, start.y);
}

//releasing a direction button stops the movement 
TEST_F(SpaceshipControlTest, DirectionButtonReleased) {
    sc.right_button_pressed();
    sc.update_spaceship(0.5f); 
    const auto mid = sc.getSpaceship().getPosition();

    sc.direction_button_released(horizontaleRichtung::RIGHT);
    sc.update_spaceship(1.0f); 
    const auto end = sc.getSpaceship().getPosition();

    EXPECT_FLOAT_EQ(end.x, mid.x);
    EXPECT_FLOAT_EQ(end.y, mid.y);
}

//nothing moves if I don't press a button
TEST_F(SpaceshipControlTest, NoMovementWithoutButton) {
    const auto start = sc.getSpaceship().getPosition();
    sc.update_spaceship(1.0f);
    const auto end = sc.getSpaceship().getPosition();

    EXPECT_FLOAT_EQ(end.x, start.x);
    EXPECT_FLOAT_EQ(end.y, start.y);
}

//we play in boundaries
TEST_F(SpaceshipControlTest, RespectBoundaries) {
    //left boundary
    sc.getSpaceship().setPosition(sf::Vector2f{constants::SPIELFELDRAND_LI, sc.getSpaceship().getPosition().y});
    sc.left_button_pressed();
    sc.update_spaceship(1.0f);

    const auto posLE = sc.getSpaceship().getPosition();
    EXPECT_GE(posLE.x, constants::SPIELFELDRAND_LI);

    //right boundary
    sc.getSpaceship().setPosition(sf::Vector2f{constants::SPIELFELDRAND_RE, sc.getSpaceship().getPosition().y});
    sc.right_button_pressed();
    sc.update_spaceship(1.0f);

    const auto posRE = sc.getSpaceship().getPosition();
    EXPECT_LE(posRE.x, constants::SPIELFELDRAND_RE);
}



