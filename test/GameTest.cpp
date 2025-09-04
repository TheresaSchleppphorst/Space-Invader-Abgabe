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
