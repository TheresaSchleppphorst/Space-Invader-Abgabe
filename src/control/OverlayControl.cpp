#include "OverlayControl.hpp"
#include "../model/Constants.hpp"
#include "../view/ILayer.hpp"

OverlayControl::OverlayControl(ILayer& layer, GameState& state) :
    font("assets/fonts/DejaVuSansMono.ttf"),
    score_view(font),
    level_view(font),
    lives_view(font),
    center_view(font),
    lives_texture(),
    lives_icon_1(lives_texture),
    lives_icon_2(lives_texture),
    lives_icon_3(lives_texture),
    layer(layer),
    state (state) {
        //position the views

        level_view.setString("Level: 1");
        level_view.setFillColor({255, 255, 255, 255});
        level_view.setCharacterSize(15);

        score_view.setString("SCORE: 0");
        score_view.setFillColor({255, 255, 255, 255});
        score_view.setCharacterSize(20);

        lives_view.setString("Lives:");
        lives_view.setFillColor({255, 255, 255, 255});
        lives_view.setCharacterSize(15);

        //load texture
        if(!
            lives_texture.loadFromFile("assets/sprites/pixilart-drawing.png"))
        throw std::invalid_argument("Could not load sprite");
        //set up sprites
        auto ts = lives_texture.getSize();

        //sprite 1
        lives_icon_1.setTexture(lives_texture, true);
        lives_icon_1.setTextureRect(sf::IntRect({0,int(ts.y) - 40}, {80, 40}));
        sf::FloatRect icon_1 = lives_icon_1.getLocalBounds();     
        lives_icon_1.setOrigin({icon_1.position.x + icon_1.size.x, icon_1.position.y + (icon_1.size.y / 2.f) }); 
        lives_icon_1.setScale({0.3, 0.3});

        //sprite 2
        lives_icon_2.setTexture(lives_texture, true);
        lives_icon_2.setTextureRect(sf::IntRect({0,int(ts.y) - 40}, {80, 40}));
        sf::FloatRect icon_2 = lives_icon_2.getLocalBounds();     
        lives_icon_2.setOrigin({icon_2.position.x + icon_2.size.x, icon_2.position.y + (icon_2.size.y / 2.f) }); 
        lives_icon_2.setScale({0.3, 0.3});

        //sprite 3
        lives_icon_3.setTexture(lives_texture, true);
        lives_icon_3.setTextureRect(sf::IntRect({0,int(ts.y) - 40}, {80, 40}));
        sf::FloatRect icon_3 = lives_icon_3.getLocalBounds();     
        lives_icon_3.setOrigin({icon_3.position.x + icon_3.size.x, icon_3.position.y + (icon_3.size.y / 2.f) }); 
        lives_icon_3.setScale({0.3, 0.3});


        //position the center view
        center_view.setPosition({constants::MITTE_X_ACHSE, constants::MITTE_Y_ACHSE});

        //function that formats the header
        layout_header();
        
}

void OverlayControl::layout_header() {

    //middle top
    sf::FloatRect b = score_view.getLocalBounds();
    score_view.setOrigin({b.position.x + (b.size.x / 2.f), b.position.y + (b.size.y / 2.f)}); //middle of the rect
    //horizontal line that helps positioning the overlayer elements
    float ausrichtungslinie = b.position.y + (b.size.y / 2.f);
    //padding to the left and right, so the text doesn't start at the outlines
    float padding_left = 5;
    float padding_right = 5;

    score_view.setPosition ({constants::MITTE_X_ACHSE, ausrichtungslinie});

    

    //left top corner
    sf::FloatRect a = level_view.getLocalBounds();
    level_view.setOrigin({a.position.x, a.position.y + (a.size.y / 2.f)}); //left middle of the rect
    level_view.setPosition({padding_left, ausrichtungslinie});

   

    //right top corner
    sf::FloatRect c = lives_view.getLocalBounds();
    lives_view.setOrigin({c.position.x + c.size.x, c.position.y + (c.size.y / 2.f)}); //right middle of the rect

    float IconBreite = lives_icon_1.getGlobalBounds().size.x; //as default because every sprite has the same size

    //set the positions of the sprites and the text
    float first = constants::VIEW_WIDTH - padding_right;

    lives_icon_1.setPosition({first, ausrichtungslinie});
    lives_icon_2.setPosition({first - padding_right - IconBreite, ausrichtungslinie});
    lives_icon_3.setPosition({first - 2* (padding_right + IconBreite), ausrichtungslinie});
    
     lives_view.setPosition({first - 3*(padding_right + IconBreite), ausrichtungslinie}); //to have a little padding to the right
}


void OverlayControl::update_score(size_t score) {
    score_view.setString("SCORE:" + std::to_string(score));
    layout_header();
}

void OverlayControl::update_lives() {

    if (lives_view.getString() != "Lives:") {
        lives_view.setString("Lives:");
        sf::FloatRect c = lives_view.getLocalBounds();
        lives_view.setOrigin({c.position.x + c.size.x, c.position.y + c.size.y / 2.f});
    }

    auto setVisible = [](sf::Sprite& s, bool on) {
        auto color = s.getColor();
        color.a = on ? 255 : 0;            
        s.setColor(color);
    };

   std::array<sf::Sprite*, 3> icons = { &lives_icon_3, &lives_icon_2, &lives_icon_1 };

    for (size_t i = 0; i < icons.size(); ++i) {
        bool on = (state.lives > i);  
        setVisible(*icons[i], on);
    }
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
    
    layer.add_to_layer(lives_icon_1);
    layer.add_to_layer(lives_icon_2);
    layer.add_to_layer(lives_icon_3);

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
    center_view.setOrigin({rc.position.x + rc.size.x/2, rc.position.y + rc.size.y/2});
}

void OverlayControl::game_won(){
    //show the center text with "YAAAAY" in blue
    show_center_view = true;
    center_view.setString("YAAAAY");
    center_view.setFillColor({0, 0, 255, 255});
    //view has to be centered according to its size
    sf::FloatRect rc = center_view.getLocalBounds();
    center_view.setOrigin({rc.position.x + rc.size.x/2, rc.position.y + rc.size.y/2});


}

void OverlayControl::hide_text(){
    show_center_view = false;
}



