#include <gtest/gtest.h>
#include "../src/view/MockLayer.hpp"

#include "../src/control/AlienControl.hpp"
#include "../src/model/Constants.hpp"

class AlienControlTest : public::testing::Test {

    public:
    AlienControlTest() : testAC(layer) {}

    protected:
    
    MockLayer layer;
    AlienControl testAC;
};

//build_Aliengrid()
TEST_F(AlienControlTest, buildsAlienGrid){
     testAC.build_Aliengrid(60,-450);
     //Checks for amount of rows:
     ASSERT_EQ(5, testAC.getAlienGrid().size());
     // int to check the y coordinates with:
     int i = 0;
    for(auto& alienrow : testAC.getAlienGrid()){
        //Checks for amount of aliens per row:
        ASSERT_EQ(11, alienrow.size());
        for(auto& alien : alienrow){
            float alienY = alien.getPosition().y;
            //check if all Y coordinates within a row are equal
            ASSERT_FLOAT_EQ(alienY, -450 + (constants::ALIEN_HEIGHT * 0.08 /2 + constants::ALIEN_HEIGHT * 0.08)*i);
        }
        i++;
    }
}

//update_aliens()
TEST_F(AlienControlTest, updatesAliens){
    // taking the float tolarance into account: (this should fix the problem)
    float epsilon = 0.0005f; 

    testAC.setSpeedControl(0.01);
    //Check Right movement:
    testAC.build_Aliengrid(60, -450);
    for(auto& row : testAC.getAlienGridRef()){
        for(auto& alien : row){
            float xBefore = alien.getPosition().x;
            testAC.update_aliens(0.001f);
            float xAfter = alien.getPosition().x;
            EXPECT_NEAR(xAfter, xBefore + 12 * 0.001f * 0.01f, epsilon);
        }
    }
    //Check left movement:
    testAC.build_Aliengrid(200, -450);
    for(auto& row : testAC.getAlienGridRef()){
        for(auto& alien : row){
            alien.setRichtungAlien(RichtungAlien::LEFT);
            float xBefore = alien.getPosition().x;
            testAC.update_aliens(0.001f);
            float xAfter = alien.getPosition().x;
            EXPECT_NEAR(xAfter, xBefore - 12 * 0.001f * 0.01f, epsilon);
        }
    }
    //Check wether the justMovedDown bool works:
    testAC.build_Aliengrid(0,0);
    testAC.update_aliens(1.0);
    //Aliens schould get moved down -> justMovedDown schould be true:
    ASSERT_TRUE(testAC.getJustMovedDown());
    testAC.build_Aliengrid(60, -450); // safe inside bounds
    testAC.update_aliens(1.0);
    //Aliens shouldnt be moved down -> justMovedDown should be false:
     ASSERT_FALSE(testAC.getJustMovedDown());
}

//move_Aliengrid_down()
TEST_F(AlienControlTest, movesAlienGridDown){
    // JustMovedDown should be true after function call:
    testAC.move_Aliengrid_down();
    ASSERT_TRUE(testAC.getJustMovedDown());
    
    auto& grid = testAC.getAlienGridRef();

    for(auto& row : grid){
        for(auto& alien : row){
            // does it switch directions? / does it move all aliens down by 12px?
            RichtungAlien vorherRichtung = alien.getRichtungAlien();
            float vorherPos = alien.getPosition().y;
            testAC.move_Aliengrid_down();
            RichtungAlien nachherRichtung = alien.getRichtungAlien();
            float nachherPos = alien.getPosition().y;
            ASSERT_NE(static_cast<int>(vorherRichtung), static_cast<int>(nachherRichtung));
            ASSERT_EQ(vorherPos +12, nachherPos);
        }
    }
}

//aliensInBounds()
TEST_F(AlienControlTest, CheckIfAliensInBounds){
    //Normal starting Position should be in Bounds 
    testAC.build_Aliengrid(60,-450);
    ASSERT_TRUE(testAC.aliensInBounds());
    //OutOfBounds on the Right:
    testAC.build_Aliengrid(constants::SPIELFELDRAND_RE + 1,-450);
    ASSERT_FALSE(testAC.aliensInBounds());
    //OutOfBounds on the Left:
    testAC.build_Aliengrid(constants::SPIELFELDRAND_LI - 1,-450);
    ASSERT_FALSE(testAC.aliensInBounds());
}

//bottomReached()
TEST_F(AlienControlTest, BottomWasReached){
    //AlienGrid that reached the Bottom:
    testAC.build_Aliengrid(60, constants::SPIELFELDRAND_UNTEN_ALIEN);
    ASSERT_TRUE(testAC.bottomReached());
    //AlienGrid that doesnt hit the Bottom Boundry:
    testAC.build_Aliengrid(60, -500);
    ASSERT_FALSE(testAC.bottomReached());
    //Test that this assumption is not dependent on the X coordinate:
    testAC.build_Aliengrid(0, constants::SPIELFELDRAND_UNTEN_ALIEN);
    ASSERT_TRUE(testAC.bottomReached());
    testAC.build_Aliengrid(-1, constants::SPIELFELDRAND_UNTEN_ALIEN);
    ASSERT_TRUE(testAC.bottomReached());
    testAC.build_Aliengrid(1000, constants::SPIELFELDRAND_UNTEN_ALIEN);
    ASSERT_TRUE(testAC.bottomReached());
}


//getAllAliens()
TEST_F(AlienControlTest, GetsAllAliens){
    testAC.getAlienGridRef().clear();
    //building a test Grid A:
    Aliens a = Aliens({0,0});
    a.setAlive(false);          //modify some alive states, dead aliens shouldnt be returned
    Aliens b = Aliens({1,0});
    Aliens c = Aliens({2,0});
    Aliens d = Aliens({0,1});
    d.setAlive(false);
    Aliens e = Aliens({1,1});
    e.setAlive(false);
    Aliens f = Aliens({2,1});
    //create two rows:
    std::vector<Aliens> first;
    std::vector<Aliens> second;
    //fill the two rows:
    first.push_back(a);
    first.push_back(b);
    first.push_back(c);
    second.push_back(d);
    second.push_back(e);
    second.push_back(f);
    //fill alien_grid:
    testAC.getAlienGridRef().push_back(first);
    testAC.getAlienGridRef().push_back(second);
    
    auto aliens = testAC.getAllAliens();

    //check correct size:
    ASSERT_EQ(aliens.size(), 2);

    //check if pointers are correct:
    EXPECT_EQ(aliens[0], &testAC.getAlienGridRef()[0][1]);
    EXPECT_EQ(aliens[1], &testAC.getAlienGridRef()[1][2]);

    //check if all returned aliens are alive:
    for (auto* alien : aliens) {
        EXPECT_TRUE(alien->getAlive());
    }
}

//alienShoot()
TEST_F(AlienControlTest, AlienShoot) {
// test to see if only one alien shoots
    // build test grid
    testAC.build_Aliengrid(100, 200);

    Aliens* a = &testAC.getAlienGridRef()[0][0];
    testAC.alienShoot(a);

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(1); // checks if there is only one shoot 

    testAC.draw_shoot();
}

//random_shoot()
// test to check if only the alive aliens shoot
TEST_F(AlienControlTest, RandomShootOnlyIfAlive) {
    //building a test Grid with only one living alien:
   auto& grid = testAC.getAlienGridRef();
   for (auto& row : grid) for (auto& al : row) al.setAlive(false);
   grid[0][1].setAlive(true); // genau einer lebt


    testAC.random_shoot(10); // there has to be a shoot after 10 seconds

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(1); // checks if there is only 1 shoot
    testAC.draw_shoot();
}


//update_shoot()
TEST_F(AlienControlTest, UpdateShootRemoved) {
// tests if shoots outside the view get deleted
    // build test grid
    testAC.build_Aliengrid(100, 200);
    Aliens* a = &testAC.getAlienGridRef()[0][0];
    testAC.alienShoot(a);

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(1); // one shoot
    testAC.draw_shoot();
    ::testing::Mock::VerifyAndClearExpectations(&layer);

    testAC.setSpeed(1000);
    testAC.update_shoot(10);

    EXPECT_CALL(layer, add_to_layer(::testing::_)).Times(0); // no shoot 
    testAC.draw_shoot();
}

