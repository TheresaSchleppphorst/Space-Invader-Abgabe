#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Graphics.hpp>

#include "../src/control/AlienControl.hpp"
#include "../src/model/Constants.hpp"

class AlienControlTest : public::testing::Test {

    public:
    AlienControlTest() : window(sf::VideoMode(1,1,32), "test",sf::Style::None),
    layer(window),
    testAC(layer){
        window.setVisible(false);
    }

    protected:
    sf::RenderWindow window;
    Layer layer;
    AlienControl testAC;
};

//build_Aliengrid()
TEST_F(AlienControlTest, buildsAlienGrid){
     testAC.build_Aliengrid();
     //Checks for amount of rows:
     ASSERT_EQ(5, testAC.getAlienGrid().size());
    for(auto& alienrow : testAC.getAlienGrid()){
        //Checks for amount of aliens per row:
        ASSERT_EQ(11, alienrow.size());
        for(auto& alien : alienrow){
            float alienY = alien.getPosition().y;
            ASSERT_THAT(alienY, )
        }
    }
    

    //TODO fix this 
}

//update_aliens()
TEST_F(AlienControlTest, updatesAliens){
    // TODO write Test
}

//move_Aliengrid_down()
TEST_F(AlienControlTest, movesAlienGridDown){

}

//aliensInBounds()
TEST_F(AlienControlTest, aliensInBoundsreturn){

}

//bottomReached()

//getAllAliens()

//alienShoot()

//random_shoot()

//update_shoot()
