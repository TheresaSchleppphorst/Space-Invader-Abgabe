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

    //Test F - hits and score
    
}



TEST_F(GameTest, SpaceshipCollisionWorks){
    g.getSpaceship().getSpaceship().setPosition({0,0});
    
    std::vector<Shoot>& shoots =  g.getAliens().getShoots();
    shoots.clear();

    //Test A - Spaceship gets hit:
    Shoot testA = Shoot({0,0});
    testA.setAlienShootSprite();

    shoots.push_back(testA);

    ASSERT_TRUE(g.collisionSpaceship());
    ASSERT_FALSE(shoots [0].getActive());
    
    //Test B - Spaceship doesnt get hit cause the shot is inactive:
    Shoot testB = Shoot({0,0});
    testB.setAlienShootSprite();
    testB.setActive(false);

    shoots.clear();
    shoots.push_back(testB);

    ASSERT_FALSE(g.collisionSpaceship());
    ASSERT_FALSE(shoots [0].getActive());

    //Test C - Spaceship doesnt get hit since theres no collision:
    Shoot testC1 = Shoot({100,30});
    Shoot testC2 = Shoot({50,0});
    testC1.setAlienShootSprite();
    testC2.setAlienShootSprite();

    shoots.clear();
    shoots.push_back(testC1);
    shoots.push_back(testC2);

    ASSERT_FALSE(g.collisionSpaceship());
    ASSERT_TRUE(shoots [0].getActive());
    ASSERT_TRUE(shoots [1].getActive());
    ASSERT_EQ(shoots.size(), 2);
}

TEST_F(GameTest, PowerupCollisionWorks){

    //powerup and spaceship on the same position makes a collison

    g.getSpaceship().getSpaceship().setPosition({0,0});
    
    
    g.getPowerup().getPowerup().setPosition({0, 0});
    g.getPowerup().set_powerup_active(true);


    ASSERT_TRUE(g.collisionPowerup());
}

TEST_F(GameTest, PowerupSpeedWorks){

    //powerup and spaceship on the same position makes a collison
    bool equal = false;

    g.getSpaceship().getSpaceship().setPosition({0,0});
    // speed before:
    float speedBefore = g.getSpaceship().getSpeed();
    
    
    g.getPowerup().getPowerup().setPosition({0, 0});
    g.getPowerup().set_powerup_active(true);

    g.update(0.1);

    float speedAfter = g.getSpaceship().getSpeed();

    if(speedAfter == speedBefore + 300 || speedAfter == speedBefore - 200){
        equal = true;
    }

    ASSERT_TRUE(equal);
}

TEST_F(GameTest, SpaceshipHit) {
    //lives decrement when the spaceship is hit
    int prevLives = g.getState().lives;

    
    g.getAliens().getShoots().clear();
    Shoot alienShot(g.getSpaceship().getSpaceship().getPosition());
    alienShot.setAlienShootSprite();
    g.getAliens().getShoots().push_back(alienShot);
  
    g.update(0);

    EXPECT_EQ(g.getState().lives, prevLives - 1);
}

/**TEST_F(GameTest, AlienHit){
    
    int prevScore = g.getState().score;

    g.getAliens().getAlienGridRef().clear();
    g.getAliens().getAlienGridRef().push_back({ Aliens({0,0}) });
    auto &alien = g.getAliens().getAlienGridRef()[0][0];
    alien.getSprite().setPosition({0,0});   

    g.getSpaceship().getShotsRef().clear();
    Shoot s({0,0});
    Shoot s({alien.getSprite().getPosition()});                
    g.getSpaceship().getShotsRef().push_back(s);

    g.update(0.0f);

    EXPECT_EQ(g.getState().score, prevScore + 10);

}
*/

