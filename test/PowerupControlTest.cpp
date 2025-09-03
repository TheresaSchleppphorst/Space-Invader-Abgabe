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

    ::testing::Mock::VerifyAndClearExpectations(&layer);

    powerup_triggern();

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(::testing::Exactly(1));
    pc.draw_powerup();
}

TEST_F(PowerupControlTest, PowerupDeletion){

    SpaceshipControl sc(layer);

    pc.set_powerup_active(true);

    pc.delete_powerup(sc);
    
    ASSERT_FALSE(pc.get_powerup_active());

}

TEST_F(PowerupControlTest, CorrectMovement){
    powerup_triggern();

    sf::Vector2f startPOS = pc.getPowerup().getPosition();
    float elapsed = 1.0f;

    pc.update_powerup(elapsed);

    sf::Vector2f newPOS = pc.getPowerup().getPosition();
    EXPECT_GT(newPOS.y, startPOS.y);
}

TEST_F(PowerupControlTest, NoDoubleActivation) {
    pc.set_powerup_active(true);
    pc.setNextPowerupTime(0.f);

    sf::Vector2f oldPOS = pc.getPowerup().getPosition();
    pc.new_powerup(1.0f);

    EXPECT_TRUE(pc.get_powerup_active());
    EXPECT_EQ(pc.getPowerup().getPosition(), oldPOS);

}

TEST_F(PowerupControlTest, NoTimerActivation) {
    pc.set_powerup_active(false);
    pc.setNextPowerupTime(10.0f); 

    pc.new_powerup(1.0f);

    EXPECT_FALSE(pc.get_powerup_active());
}

TEST_F(PowerupControlTest, TimerActivation) {
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
