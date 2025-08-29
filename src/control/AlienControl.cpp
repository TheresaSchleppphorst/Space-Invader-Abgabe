#include "AlienControl.hpp"
#include "../model/Aliens.hpp"
#include "../model/Constants.hpp"
#include "../model/Shoot.hpp"
#include <iostream>
// this is just needed for a quick test in update_alien:
// using namespace std; 


AlienControl::AlienControl(Layer &layer) : layer(layer), random_engine(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()))
        {
    AlienControl::build_Aliengrid();
    nextShoot_time = time_between_shoot(random_engine);
}

void AlienControl::build_Aliengrid() {

    // Create the Alien grid.
    int level_depth = 5;

    // Creates an alien_grid depending on the required Level_depth.
    for (int i = 0; i < level_depth; i++){
        std::vector<Aliens> alien_row;
        float ifloat = static_cast<float>(i);

        // Fills the created alien_row with 11 Aliens each.
        for (int j = 0; j < 11; j++){
            float jfloat = static_cast<float>(j);
            Aliens newAlien = Aliens({72 + (24+15)*jfloat,-500 + (16+12)*ifloat});
            alien_row.push_back(newAlien);
        }

        // Adds the now filled alien_row to the alien_grid.
        alien_grid.push_back(alien_row);
    }
}

void AlienControl::update_aliens(float elapsed_time){

    if(bottomReached()) {
        // TODO write gameOver() function
        // this is the test needing the statement at the top:
        // cout << "Game would be over now!";
    };

    // Incase theres need to alter the speed.
    float speedControl = 4.0;

    if(!aliensInBounds() && !justMovedDown){
                    move_Aliengrid_down();
            }

    // the Grid moves right until the first alien hits the SPIELFELDRAND_RE,
    for(auto& row : alien_grid){
        for(auto& alien: row){

             // horrizontal position of the alien.
            float x = alien.getPosition().x;
            // vertical position of the alien.
            float y = alien.getPosition().y;

            // Move alien depending on RichtungAlien.
            float movement = 12;
            if(alien.getRichtungAlien() == RichtungAlien::LEFT) {
                movement = - movement;
            }

            x = alien.getPosition().x + movement * elapsed_time * speedControl;

            //update position
            y = alien.getPosition().y;
            alien.setPosition({x, y});
        }
    }
    if(aliensInBounds()){
        justMovedDown = false;
    }

    random_shoot(elapsed_time);
    update_shoot(elapsed_time);

}

void AlienControl::draw_aliens(){
    // For every Row in the Alien Grid ...
    for(auto& row : alien_grid ) {
        // For every Alien in the Row ...
        for(auto& alien : row){
             layer.add_to_layer(alien.getSprite());
        }
    }
}

void AlienControl::draw_shoot(){
        for(const auto& shoot: shoots){
        layer.add_to_layer(shoot.getSprite());}
}

void AlienControl::move_Aliengrid_down() {

    for(auto& row : alien_grid){
        for(auto& alien : row){
            
            float y = alien.getPosition().y;
            float x = alien.getPosition().x;
            // testen ob + oder -:
            // (16+12) is an estimate can be change to our liking. Since all Aliens are moved down we dont need to consider spacing so much.
            alien.setPosition({x,y + (12)});
            // Switch Direction from left to right, or right to left:
            if(alien.getRichtungAlien() == RichtungAlien::RIGHT){
                alien.setRichtungAlien(RichtungAlien::LEFT);
        }
        else if(alien.getRichtungAlien() == RichtungAlien::LEFT){
                alien.setRichtungAlien(RichtungAlien::RIGHT);
            }
    }
}
justMovedDown = true;
}

bool AlienControl::aliensInBounds(){
    bool inBounds = true;

    for(auto& row : alien_grid){

        if(row.front().getPosition().x < constants::SPIELFELDRAND_LI || row.back().getPosition().x > constants::SPIELFELDRAND_RE) {

            inBounds = false;
    }
}
 return inBounds;
}

// checks if the bottom boundry has been breached.
bool AlienControl::bottomReached(){

    bool reached;
    for(auto& row : alien_grid){
        for(auto& alien : row){
            if (alien.getPosition().y == constants::SPIELFELDRAND_UN){
                reached = true;
            }
        }
    }
    
return reached;
}

std::vector<Aliens*> AlienControl::getShootingAliens() {
    std::vector<Aliens*> lowest;
    int reihe = alien_grid[0].size();
    for (int j = 0; j < reihe; j++) {
        for (int i = alien_grid.size()-1; i >= 0; i--) {
            if (true) {
                lowest.push_back(&alien_grid[i][j]);
                break;
            }
        }
    }
    return lowest;
}


void AlienControl::alienShoot(Aliens* sAlien) {

    auto pos = sAlien->getPosition();
    shoots.emplace_back(pos);
    auto& s = shoots.back();
    s.setAlienShootSprite(); // anderes Sprite (blaue Schüsse)
    s.setPosition({pos.x, pos.y - 15 });
    s.move_down(); // Bewegungsrichtung nach unten
}

void AlienControl::random_shoot(float elapsed_time) {
    nextShoot_time -= elapsed_time;
    if (nextShoot_time > 0) return;

    auto shooters = getShootingAliens();
    if (!shooters.empty()) {
        std::uniform_int_distribution<size_t> pick(0, shooters.size()-1);
        Aliens* a = shooters[pick(random_engine)];

        // Schießen
        alienShoot(a);
    }

    nextShoot_time = time_between_shoot(random_engine); // nächstes Intervall
}


void AlienControl::update_shoot(float elapsed_time) {
    if(shoots.empty() == false){

    float speed = 200; // Alien Schüssen sind langsamer als die vom Raumschiff (einfacher zu spielen)

    for(auto& shoot : shoots){
        float x = shoot.getPosition().x;
        float y = shoot.getPosition().y;

    if (shoot.getVertikaleRichtung() == vertikaleRichtung::DOWN) {
        y += elapsed_time * speed;
        // update position
        shoot.setPosition({x, y});
    }
    }

    // Verschwinden der Schüsse:
    
    for (auto shootIterator = shoots.begin(); shootIterator != shoots.end(); ) {
       if (shootIterator->getSprite().getPosition().y >= constants::MITTE.y - 300) {
            shootIterator = shoots.erase(shootIterator);
       } else 
            shootIterator++;
    }
}
}
    


