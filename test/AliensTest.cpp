#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/model/Aliens.hpp"
#include "../src/model/Constants.hpp"

class AliensTest : public ::testing::Test {

public:
    AliensTest() : a(constants::MITTE) {}

protected:
    Aliens a;
};

TEST_F(AliensTest, Initialization) {
    //position is initialized correctly depending on the given parameter alienpos
    ASSERT_EQ(a.getPosition().x, constants::MITTE_X_ACHSE);
    ASSERT_EQ(a.getPosition().y, constants::MITTE_Y_ACHSE);

    //bounds are greater than null
    const auto& sp = a.getSprite();
    const auto gb = sp.getGlobalBounds();
    EXPECT_GT(gb.size.x, 0);
    EXPECT_GT(gb.size.y, 0);
}

TEST_F(AliensTest, MovementRight){
   //movement to the right
  a.move_right();
  EXPECT_EQ(a.getRichtungAlien(), RichtungAlien::RIGHT);

  //further movement to the right changes nothing
  a.move_right();
  a.move_right();
  EXPECT_EQ(a.getRichtungAlien(), RichtungAlien::RIGHT);

  //movement from left to right sets correctly
  a.move_left();
  a.move_right();
  EXPECT_EQ(a.getRichtungAlien(), RichtungAlien::RIGHT);
}

TEST_F(AliensTest, MovementLeft){
    //movement to the left
    a.move_left();
    EXPECT_EQ(a.getRichtungAlien(), RichtungAlien::LEFT);

    //further movement to the left changes nothing
    a.move_left();
    a.move_left();
    EXPECT_EQ(a.getRichtungAlien(), RichtungAlien::LEFT);

    //movement from right to left sets correctly
    a.move_right();
    a.move_left();
    EXPECT_EQ(a.getRichtungAlien(), RichtungAlien::LEFT);
}

