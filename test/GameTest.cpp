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

TEST_F(GameTest, AlienCollisionsWorks){
    g.getAliens().getAlienGridRef().clear();

    //make test Grid:
    // a gets hit
    // b doenst cause shoot is inactive
    // c doesnt cause alien is already dead
    // d gets hit

    Aliens a = Aliens({0,0});
    Aliens b = Aliens({100,0});
    Aliens c = Aliens({0,100});
    c.setAlive(false);
    Aliens d = Aliens({100,100});

    std::vector<Aliens> first;
    std::vector<Aliens> second;

    first.push_back(a);
    first.push_back(b);
    second.push_back(c);
    second.push_back(d);

    g.getAliens().getAlienGridRef().push_back(first);
    g.getAliens().getAlienGridRef().push_back(second);

    //Test A:
    Shoot testA = Shoot({0,0});
    g.getSpaceship().getShotsRef().clear();
    g.getSpaceship().getShotsRef().push_back(testA);

    ASSERT_TRUE(g.collisionAlien());
    ASSERT_FALSE(g.getSpaceship().getShotsRef() [0].getActive());
    ASSERT_FALSE(g.getAliens().getAlienGridRef()[0][0].getAlive());

    //Test B:
    Shoot testB = Shoot({100,0});
    testB.setActive(false);

    g.getSpaceship().getShotsRef().clear();
    g.getSpaceship().getShotsRef().push_back(testB);

    ASSERT_FALSE(g.collisionAlien());
    ASSERT_FALSE(g.getSpaceship().getShotsRef() [0].getActive());
    ASSERT_TRUE(g.getAliens().getAlienGridRef()[0][1].getAlive());

    //Test C:
    Shoot testC = Shoot({0,100});

    g.getSpaceship().getShotsRef().clear();
    g.getSpaceship().getShotsRef().push_back(testC);

    ASSERT_FALSE(g.collisionAlien());
    ASSERT_TRUE(g.getSpaceship().getShotsRef() [0].getActive());
    ASSERT_FALSE(g.getAliens().getAlienGridRef()[1][0].getAlive());

    //Test D:
    Shoot testD = Shoot({100,100});

    g.getSpaceship().getShotsRef().clear();
    g.getSpaceship().getShotsRef().push_back(testD);

    ASSERT_TRUE(g.collisionAlien());
    ASSERT_FALSE(g.getSpaceship().getShotsRef() [0].getActive());
    ASSERT_FALSE(g.getAliens().getAlienGridRef()[1][1].getAlive());

    g.getAliens().getAlienGridRef().clear();

    //Test E - Empty Grid:
    
    Shoot testE = Shoot({100,100});
    g.getSpaceship().getShotsRef().push_back(testE);

    ASSERT_FALSE(g.collisionAlien());
    ASSERT_FALSE(g.getSpaceship().getShotsRef() [0].getActive());
    ASSERT_TRUE(g.getSpaceship().getShotsRef() [1].getActive());
}
