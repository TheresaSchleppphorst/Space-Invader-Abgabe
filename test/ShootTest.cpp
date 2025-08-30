#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/model/Shoot.hpp"
#include "../src/model/Constants.hpp"

class ShootTest : public ::testing::Test {

public:
    ShootTest() : s(constants::MITTE) {}

protected:
    Shoot s;
};

TEST_F(ShootTest, Initialization) {
    //position is initialized correctly depending on the given parameter alienpos
    ASSERT_EQ(s.getPosition().x, constants::MITTE_X_ACHSE);
    ASSERT_EQ(s.getPosition().y, constants::MITTE_Y_ACHSE);

    //bounds are greater than null
    const auto& sp = s.getSprite();
    const auto gb = sp.getGlobalBounds();
    EXPECT_GT(gb.size.x, 0);
    EXPECT_GT(gb.size.y, 0);
}

TEST_F(ShootTest, MovementUp){
    //movement up
    s.move_up();
    EXPECT_EQ(s.getVertikaleRichtung(), vertikaleRichtung::UP);

  //further movement to the top changes nothing
  s.move_up();
  s.move_up();
  EXPECT_EQ(s.getVertikaleRichtung(), vertikaleRichtung::UP);

  //movement from down to up sets correctly
  s.move_down();
  s.move_up();
  EXPECT_EQ(s.getVertikaleRichtung(), vertikaleRichtung::UP);
}

TEST_F(ShootTest, MovementDown){
    //movement down
    s.move_down();
    EXPECT_EQ(s.getVertikaleRichtung(), vertikaleRichtung::DOWN);

  //further movement to the bottom changes nothing
  s.move_down();
  s.move_down();
  EXPECT_EQ(s.getVertikaleRichtung(), vertikaleRichtung::DOWN);

  //movement from up to down sets correctly
  s.move_up();
  s.move_down();
  EXPECT_EQ(s.getVertikaleRichtung(), vertikaleRichtung::DOWN);
}
