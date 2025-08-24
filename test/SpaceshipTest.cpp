
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/model/Spaceship.hpp"
#include "../src/model/Constants.hpp"

class SpaceshipTest : public ::testing::Test {

protected:
    Spaceship s;
};

TEST_F(SpaceshipTest, Initialization) {
    //position is initialized correctly
    ASSERT_EQ(s.getPosition().x, constants::MITTE_X_ACHSE);
    ASSERT_EQ(s.getPosition().y, -10);

     //bounds are greater than null
    const auto& sp = s.getSprite();
    const auto gb = sp.getGlobalBounds();
    EXPECT_GT(gb.size.x, 0);
    EXPECT_GT(gb.size.y, 0);
}

TEST_F(SpaceshipTest, MovementRight){
  //initial value of horizontaleRichtung
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::NONE);

  //movement to the right
  s.move_right();
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::RIGHT);

  //further movement to the right changes nothing
  s.move_right();
  s.move_right();
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::RIGHT);

  //movement from left to right sets correctly
  s.move_left();
  s.move_right();
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::RIGHT);
}

TEST_F(SpaceshipTest, MovementLeft){
    //initial value of horizontaleRichtung
    EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::NONE);

    //movement to the left
    s.move_left();
    EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::LEFT);

    //further movement to the left changes nothing
    s.move_left();
    s.move_left();
    EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::LEFT);

    //movement from right to left sets correctly
    s.move_right();
    s.move_left();
    EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::LEFT);
}

TEST_F(SpaceshipTest, StopMovement){
  //movement to the right stops correctly
  s.move_right();
  s.stop_horizontal_movement();
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::NONE);

  //movement to the left stops correctly
  s.move_left();
  s.stop_horizontal_movement();
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::NONE);

  //stopping after stopping does not change the state
  s.stop_horizontal_movement();
  s.stop_horizontal_movement();
  EXPECT_EQ(s.getHorizontaleRichtung(), horizontaleRichtung::NONE);
}

