#include <gtest/gtest.h>
#include "../src/view/MockLayer.hpp"

#include "../src/control/OverlayControl.hpp"
#include "../src/model/Constants.hpp"


using ::testing::NiceMock;

class OverlayControlTest : public ::testing::Test {

public:
 OverlayControlTest() : oc(layer, state) {}


protected:
    NiceMock<MockLayer> layer;
    GameState state{};
    OverlayControl oc;

    static int countVisibleLives(const OverlayControl& oc) {
    int visible = 0;
    if (oc.getLivesIcon_3().getColor().a > 0) ++visible; 
    if (oc.getLivesIcon_2().getColor().a > 0) ++visible; 
    if (oc.getLivesIcon_1().getColor().a > 0) ++visible; 
    return visible;
}
};

TEST_F(OverlayControlTest, UpdateScore){
    //sets string correctly
    oc.update_score(123);

    EXPECT_EQ(oc.getScoreView().getString(), "SCORE:123");
    EXPECT_FLOAT_EQ(oc.getScoreView().getPosition().x, constants::MITTE_X_ACHSE);

    //origin is correct
    auto a = oc.getScoreView().getLocalBounds();
    auto b = oc.getScoreView().getOrigin();
    EXPECT_NEAR(b.x, a.position.x + a.size.x / 2.f, 0.5f);
    EXPECT_NEAR(b.y, a.position.y + a.size.y / 2.f, 0.5f);
}


TEST_F(OverlayControlTest, UpdateLevel){
    //sets string correctly
    oc.update_level(8);

    EXPECT_EQ(oc.getLevelView().getString().toAnsiString(), "Level:8");
    EXPECT_FLOAT_EQ(oc.getLevelView().getPosition().y, oc.getScoreView().getPosition().y);
}

TEST_F(OverlayControlTest, UpdateLives){
    for (int lives = 0; lives <= 3; ++lives) {
        state.lives = lives;
        oc.update_lives();

        int visible = countVisibleLives(oc);
        EXPECT_EQ(visible, lives);
        
    }
}

TEST_F(OverlayControlTest, GameOver) {
    oc.game_over();
    EXPECT_TRUE(oc.isCenterThere());

    //test text and color
    EXPECT_EQ(oc.getCenterView().getString().toAnsiString(), "Game Over");
    auto color = oc.getCenterView().getFillColor();
    EXPECT_EQ(color.r, 255);
    EXPECT_EQ(color.g, 0);
    EXPECT_EQ(color.b, 0);
    EXPECT_EQ(color.a, 255);

    //test position and origin
    auto a = oc.getCenterView().getLocalBounds();
    auto b = oc.getCenterView().getOrigin();
    EXPECT_NEAR(b.x, a.position.x + a.size.x / 2.f, 0.5f);
    EXPECT_NEAR(b.y, a.position.y + a.size.y / 2.f, 0.5f);
    auto pos = oc.getCenterView().getPosition();
    EXPECT_FLOAT_EQ(pos.x, constants::MITTE_X_ACHSE);
    EXPECT_FLOAT_EQ(pos.y, constants::MITTE_Y_ACHSE);
}

TEST_F(OverlayControlTest, GameWon) {
    oc.game_won();
    EXPECT_TRUE(oc.isCenterThere());

    //test text and color
    EXPECT_EQ(oc.getCenterView().getString().toAnsiString(), "YAAAAY");
    auto color = oc.getCenterView().getFillColor();
    EXPECT_EQ(color.r, 0);
    EXPECT_EQ(color.g, 0);
    EXPECT_EQ(color.b, 255);
    EXPECT_EQ(color.a, 255);

    //test position and origin
    auto a = oc.getCenterView().getLocalBounds();
    auto b = oc.getCenterView().getOrigin();
    EXPECT_NEAR(b.x, a.position.x + a.size.x / 2.f, 0.5f);
    EXPECT_NEAR(b.y, a.position.y + a.size.y / 2.f, 0.5f);
    auto pos = oc.getCenterView().getPosition();
    EXPECT_FLOAT_EQ(pos.x, constants::MITTE_X_ACHSE);
    EXPECT_FLOAT_EQ(pos.y, constants::MITTE_Y_ACHSE);
}