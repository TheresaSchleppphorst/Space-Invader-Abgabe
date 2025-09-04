#include "PowerupControl.hpp"
#include "../model/Constants.hpp"
#include <cmath>

#include <iostream>


PowerupControl::PowerupControl(ILayer& layer) : powerup(sf::Vector2f{0, 0}), layer(layer), random_engine(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()))
        {
            nextPowerup_time = time_between_powerup(random_engine);
        }

bool PowerupControl::get_powerup_active(){
    return powerup_active;
}

bool PowerupControl::get_good_powerup(){
    return good_powerup;
}

void PowerupControl::update_powerup(float elapsed_time){

    new_powerup(elapsed_time);

    if (!powerup_active) return;

    // falling down (constant speed) 
    auto pos = powerup.getPosition();
    pos.y += powerup_speed * elapsed_time;
    powerup.setPosition(pos);

    // timer for the next powerup, if its out of the SPIELFELD
    if (pos.y > constants::SPIELFELDRAND_UN) {
        nextPowerup_time = time_between_powerup(random_engine);
        powerup_active = false;

        //std::cout << "TEEEEEEEST " << powerup_active << std::endl;
        //inline test that poweruup_active returns false at this moment
    }
}

void PowerupControl:: delete_powerup(SpaceshipControl& sc){
    powerup_active = false;
    sc.deactivate_powerup();
    
}

void PowerupControl::draw_powerup(){
    if(powerup_active){
    layer.add_to_layer(powerup.getSprite());}
}

void PowerupControl::new_powerup(float elapsed_time){
    
    if (powerup_active) return;
    nextPowerup_time -= elapsed_time;

    if (nextPowerup_time > 0.f) return;

    // random x-position 
    const float minX  = constants::SPIELFELDRAND_LI + 50; // 50 is half the powerup sprite
    const float maxX = constants::SPIELFELDRAND_RE - 50;
    std::uniform_real_distribution<float> xdist(minX, maxX);
    const float x = xdist(random_engine);

    // y-position at the top display edge
    const float y = -constants::VIEW_HEIGHT;

    powerup.setPosition({x, y});

    // good and bad powerUps switch
   if (good_powerup){ 
    powerup.setBadPowerupSprite();
    good_powerup = false;
    }
   else {
        powerup.setGoodPowerupSprite();
        good_powerup= !good_powerup;}

    powerup.move_down();      // movement from top to bottom 
    powerup_active = true;

    nextPowerup_time = time_between_powerup(random_engine); // next interval 
}
