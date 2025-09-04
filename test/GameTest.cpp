#include <gtest/gtest.h>
#include "../src/view/MockLayer.hpp"

#include "../src/control/Game.hpp"
#include "../src/model/Constants.hpp"



class GameTest : public ::testing::Test {


protected:
    Game g;
};




TEST_F(GameTest, ZeroLivesGameOver){
    //after updating lives = 0 -> game over
    g.getState().lives = 0;
    g.update(0.0f);
    const auto& centerview = g.getOverlay().getCenterView();
    EXPECT_EQ(centerview.getString().toAnsiString(), "Game Over");
    EXPECT_EQ(g.getPhase(), GamePhase::gameOver);
}

TEST_F(GameTest, LevelWon){
    g.start_next_level();
    g.getAliens().getAlienGridRef().clear();

    g.update(0.0f);

    const auto& centerview = g.getOverlay().getCenterView();
    EXPECT_EQ(centerview.getString().toAnsiString(), "YAAAAY");
    EXPECT_EQ(g.getPhase(), GamePhase::levelCleared); //optional, keine Ahnung ob das funktioniert, sonst weglassen
}


TEST_F(GameTest, Reset){
    g.getState().score = 200;
    g.getState().level = 5;
    g.getState().lives = 1;

    g.reset_game();

    EXPECT_EQ(g.getState().score, 0);
    EXPECT_EQ(g.getState().level, 1);
    EXPECT_EQ(g.getState().lives, 3);

    EXPECT_FALSE(g.getAliens().getAlienGridRef().empty());

}


TEST_F(GameTest, Start){
    for(auto& row : g.getAliens().getAlienGridRef()){
        for(auto& a : row) {
            a.setAlive(false);
        }
    }
    g.start_next_level();

    EXPECT_FALSE(g.getAliens().getAlienGridRef().empty());
}

TEST_F(GameTest, CollisionGoodPowerup) {
    auto& sp = g.getSpaceship();  // SpaceshipControl&
    auto& pu = g.getPowerup();    // PowerupControl&

    const float base = sp.getSpeed();

    // good powerup:
    pu.getPowerup().setGoodPowerupSprite();
    pu.set_powerup_active(true);
    pu.set_good_powerup(true);
    pu.getPowerup().setPosition({200,-200});
    
    sp.getSpaceship().setPosition({200, -200});

    g.update(0);

    // shoot should be faster
    EXPECT_FLOAT_EQ(sp.getSpeed(), base + 300);
    // set back to normal speed
    sp.deactivate_powerup();
    EXPECT_FLOAT_EQ(sp.getSpeed(), base);
}

TEST_F(GameTest, CollisionBadPowerup) {
    auto& sp = g.getSpaceship();  // SpaceshipControl&
    auto& pu = g.getPowerup();    // PowerupControl&

    const float base = sp.getSpeed();

    // good powerup:
    pu.getPowerup().setBadPowerupSprite();
    pu.set_powerup_active(true);
    pu.set_good_powerup(false);
    pu.getPowerup().setPosition({200,-200});
    
    sp.getSpaceship().setPosition({200, -200});

    g.update(0);

    // shoot should be slower
    EXPECT_FLOAT_EQ(sp.getSpeed(), base - 200);
    // set back to normal speed
    sp.deactivate_powerup();
    EXPECT_FLOAT_EQ(sp.getSpeed(), base);
}


