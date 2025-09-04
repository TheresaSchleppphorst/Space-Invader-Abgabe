#include <gtest/gtest.h>
#include "../src/view/MockLayer.hpp"

#include "../src/control/PowerupControl.hpp"
#include "../src/control/SpaceshipControl.hpp"
#include "../src/model/Constants.hpp"


using ::testing::NiceMock;

class PowerupControlTest : public ::testing::Test {

public:
 PowerupControlTest() : pc(layer) {}


protected:
    NiceMock<MockLayer> layer;
    PowerupControl pc;

    //function that triggers a powerup
    void powerup_triggern() {
    pc.new_powerup(1000.0f);                
    ASSERT_TRUE(pc.get_powerup_active());
    }
};



TEST_F(PowerupControlTest, DrawPowerup){
    //powerup is drawn correcly

    ::testing::Mock::VerifyAndClearExpectations(&layer);

    powerup_triggern();

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(1));
    pc.draw_powerup();
}

TEST_F(PowerupControlTest, PowerupDeletion){
    //the deletion sets the powerup_active = false
    SpaceshipControl sc(layer);
    pc.set_powerup_active(true);
    pc.delete_powerup(sc);
    ASSERT_FALSE(pc.get_powerup_active());

}

TEST_F(PowerupControlTest, CorrectMovement){
    //powerup moves downwards
    powerup_triggern();

    sf::Vector2f startPOS = pc.getPowerup().getPosition();
    float elapsed = 1.0f;

    pc.update_powerup(elapsed);

    sf::Vector2f newPOS = pc.getPowerup().getPosition();
    EXPECT_GT(newPOS.y, startPOS.y);
}

TEST_F(PowerupControlTest, NoDoubleActivation) {
    //a powerup can only be activated when its status was deactivated
    pc.set_powerup_active(true);
    pc.setNextPowerupTime(0.f);

    sf::Vector2f oldPOS = pc.getPowerup().getPosition();
    pc.new_powerup(1.0f);

    EXPECT_TRUE(pc.get_powerup_active());
    EXPECT_EQ(pc.getPowerup().getPosition(), oldPOS);

}

TEST_F(PowerupControlTest, NoTimerActivation) {
    //when the timer is still running, no powerup can be activated
    pc.set_powerup_active(false);
    pc.setNextPowerupTime(10.0f); 

    pc.new_powerup(1.0f);

    EXPECT_FALSE(pc.get_powerup_active());
}

TEST_F(PowerupControlTest, TimerActivation) {
    //powerup is initialized correctly when timer is over
    pc.set_powerup_active(false);
    pc.setNextPowerupTime(0.0f); 

    pc.new_powerup(1.0f);

    EXPECT_TRUE(pc.get_powerup_active());

    auto pos = pc.getPowerup().getPosition();

    float minX = constants::SPIELFELDRAND_LI + 50.f;
    float maxX = constants::SPIELFELDRAND_RE - 50.f;
    EXPECT_GE(pos.x, minX);
    EXPECT_LE(pos.x, maxX);

    EXPECT_FLOAT_EQ(pos.y, -constants::VIEW_HEIGHT);
}

TEST_F(PowerupControlTest, PowerupSwitch) {
    //powerup switches correctly between good and bad
    pc.set_powerup_active(false);
    pc.setNextPowerupTime(0.0f);

    bool wasGood = pc.get_good_powerup();
    pc.new_powerup(1.0f);
    EXPECT_NE(pc.get_good_powerup(), wasGood); 
}

TEST_F(PowerupControlTest, TimeReset) {
    //the time is reset correcty for the next powerup
    pc.set_powerup_active(false);
    pc.setNextPowerupTime(0.0f);

    pc.new_powerup(1.0f);
    EXPECT_GT(pc.getNextPowerupTime(), 0.0f);
}

TEST_F(PowerupControlTest, DoesNothingWhenInactive) {
    //the powerup doesn't change position when not activated
    pc.set_powerup_active(false);
    auto oldPos = pc.getPowerup().getPosition();
    pc.update_powerup(1.0f);
    EXPECT_EQ(pc.getPowerup().getPosition(), oldPos);
}


TEST_F(PowerupControlTest, DeactivatesWhenOutOfScreen) {
    //powerup gets deactivated when it falls out of the screen
    powerup_triggern();
    ASSERT_TRUE(pc.get_powerup_active());

    sf::Vector2f highPos = pc.getPowerup().getPosition();
    highPos.y = constants::SPIELFELDRAND_UN + 100.f; 
    pc.getPowerup().setPosition(highPos); 

    pc.update_powerup(100.0f);

    EXPECT_FALSE(pc.get_powerup_active());
    EXPECT_GT(pc.getNextPowerupTime(), 0.0f);
}

