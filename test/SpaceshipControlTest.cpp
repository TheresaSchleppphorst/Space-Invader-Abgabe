#include <gtest/gtest.h>
#include "../src/view/MockLayer.hpp"

#include "../src/control/SpaceshipControl.hpp"
#include "../src/model/Constants.hpp"


using ::testing::NiceMock;

class SpaceshipControlTest : public ::testing::Test {

public:
 SpaceshipControlTest() : sc(layer) {}


protected:
    NiceMock<MockLayer> layer;
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

TEST_F(SpaceshipControlTest, DrawSpaceship){

    ::testing::Mock::VerifyAndClearExpectations(&layer);

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(1));
    sc.draw_spaceship();
}


TEST_F(SpaceshipControlTest, DrawShoot){
    //without spacebar, there is no shoot
    ::testing::Mock::VerifyAndClearExpectations(&layer);
    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(0));
    sc.draw_shoot();

    //one spacebar equals one shoot
    sc.space_bar_pressed();
    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(1));
    sc.draw_shoot();

    //two more shoots should equal 3 shoots in total
    sc.space_bar_pressed();
    sc.space_bar_pressed();
    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(3));
    sc.draw_shoot();

}

TEST_F(SpaceshipControlTest, ClearAll) {
     ::testing::Mock::VerifyAndClearExpectations(&layer);

     sc.space_bar_pressed();
     sc.space_bar_pressed();
    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(2));
    sc.draw_shoot();

    //clear the window from shoots
    sc.clearAll();
    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(0));
    sc.draw_shoot();

}

TEST_F(SpaceshipControlTest, PowerUpDoubleActivation) {
    //powerups do not multiply their features
    ::testing::Mock::VerifyAndClearExpectations(&layer);
    sc.setSpeed(400.0f);

    sc.activate_good_powerup(2.0f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 700.0f);

    sc.activate_good_powerup(2.0f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 700.0f);

    sc.update_shoot(2.01f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 400.f);

}

TEST_F(SpaceshipControlTest, PowerUpUnique) {
    //a spaceship can only inherit one powerup
    ::testing::Mock::VerifyAndClearExpectations(&layer);
    sc.setSpeed(400.0f);

    sc.activate_good_powerup(2.0f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 700.0f);

    sc.activate_bad_powerup(2.0f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 700.0f);

    sc.update_shoot(2.01f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 400.f);

}

TEST_F(SpaceshipControlTest, UpdateShootGoodPU) {
    //testing good powerup on shoots
    ::testing::Mock::VerifyAndClearExpectations(&layer);

    sc.setSpeed(400.0f);
    sc.activate_good_powerup(1.0f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 700.0f);

    sc.update_shoot(1.01f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 400.0f);
}

TEST_F(SpaceshipControlTest, UpdateShootBadPU) {
    //testing bad powerup on shoots
     ::testing::Mock::VerifyAndClearExpectations(&layer);

    sc.setSpeed(400.0f);
    sc.activate_bad_powerup(1.0f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 200.0f);

    sc.update_shoot(1.01f);
    EXPECT_FLOAT_EQ(sc.getSpeed(), 400.0f);
}

TEST_F(SpaceshipControlTest, LinearMovement){
    const auto start = sc.getSpaceship().getPosition();
    sc.right_button_pressed();

    const float time = 0.5f;
    sc.update_spaceship(time);

    const auto end = sc.getSpaceship().getPosition();

    EXPECT_NEAR(end.x, start.x + 200.0f * time, 1e-4f); //the delta of 0.0001
    EXPECT_FLOAT_EQ(end.y, start.y);
}


TEST_F(SpaceshipControlTest, DirectionChange){
    //movement from right to left is immediate
    const auto start = sc.getSpaceship().getPosition();

    sc.right_button_pressed();
    sc.update_spaceship(0.2f);
    const auto mid = sc.getSpaceship().getPosition();
    EXPECT_GT(mid.x, start.x);

    sc.left_button_pressed();
    sc.update_spaceship(0.2f);
    const auto end = sc.getSpaceship().getPosition();
    EXPECT_LT(end.x, mid.x);

    EXPECT_FLOAT_EQ(start.y, mid.y);
    EXPECT_FLOAT_EQ(end.y, mid.y);

}