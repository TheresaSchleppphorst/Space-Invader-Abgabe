#include "OverlayControl.hpp"
#include "../model/Constants.hpp"

OverlayControl::OverlayControl(Layer &layer) :
    font("assets/fonts/DejaVuSansMono.ttf"),
    score_view(font),
    level_view(font),
    lives_view(font),
    center_view(font),
    layer(layer) {
        //position the views
       
        score_view.setString("SCORE: 0");
        score_view.setFillColor({255, 255, 255, 255});
        score_view.setCharacterSize(20);
  
    
        lives_view.setString("3");
        lives_view.setFillColor({255, 255, 255, 255});
        lives_view.setCharacterSize(20);
       
    
        level_view.setString("Level: 1");
        level_view.setFillColor({255, 255, 255, 255});
        level_view.setCharacterSize(20);

        center_view.setPosition({300, 300});

        layout_header();
        
}

void OverlayControl::layout_header() {

    //left top corner
    sf::FloatRect a = level_view.getLocalBounds();
    level_view.setPosition ({0,0});

    //middle top
    sf::FloatRect b = score_view.getLocalBounds();
    score_view.setOrigin({b.size.x / 2, 0}); //top middle of the rect
    score_view.setPosition ({constants::MITTE_X_ACHSE, 0});


    //right top corner
    sf::FloatRect c = lives_view.getLocalBounds();
    lives_view.setOrigin({c.size.x, 0}); //right top corner of the rect
    lives_view.setPosition({constants::VIEW_WIDTH - 5.f, 0}); //to have a little padding to the right


}


void OverlayControl::update_score(size_t score) {
    score_view.setString("SCORE:" + std::to_string(score));
    layout_header();
}

void OverlayControl::update_lives(int lives) {
    lives_view.setString(std::to_string(lives));
    layout_header();
}

void OverlayControl::update_level(size_t level) {
   level_view.setString("Level:" + std::to_string(level));
   layout_header();
}

void OverlayControl::draw() {
    //draw the text views to the layer
    layer.add_to_layer(score_view);
    layer.add_to_layer(lives_view);
    layer.add_to_layer(level_view);
    if(show_center_view)
        layer.add_to_layer(center_view);
}

void OverlayControl::game_over() {
    //show the center text with "Game Over" in red
    show_center_view = true;
    center_view.setString("Game Over");
    center_view.setFillColor({255, 0, 0, 255});
    //view has to be centered according to its size
    sf::FloatRect rc = center_view.getLocalBounds();
    center_view.setOrigin({rc.size.x/2, rc.size.y/2});
}



