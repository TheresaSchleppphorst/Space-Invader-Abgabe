#include "Game.hpp"
#include "AlienControl.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <vector>


Game::Game() : window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    overlay_layer(window),
    spaceship_control(game_layer),
    overlay_control(overlay_layer, state),
    alien_control(game_layer),
    powerup_control(game_layer)
    {
    // limit frame rate
    window.setFramerateLimit(constants::FRAME_RATE);
    // set the view (visible area) for our game
    game_layer.set_view(view);
    
}

void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();
 
        // handle input, check if window is still open
        if (!input()) {
            // update the scene according to the passed time
            update(elapsed_time.asSeconds());
            // draw the scene
            draw();
        }
    }
}

// returns true, if the window has been closed
bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }
       if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyReleased->code == sf::Keyboard::Key::Left) {
                // stop moving left
                spaceship_control.direction_button_released(horizontaleRichtung::LEFT);
            } else if (keyReleased->code == sf::Keyboard::Key::Right) {
                // stop moving right
                spaceship_control.direction_button_released(horizontaleRichtung::RIGHT);
            }
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Right) {
                // move right
                spaceship_control.right_button_pressed();
            } else if (keyPressed->code == sf::Keyboard::Key::Left) {
                // move left
                spaceship_control.left_button_pressed();
            }
             // shooting with space bar
            else if (keyPressed->code == sf::Keyboard::Key::Space) {
                 spaceship_control.space_bar_pressed();
            }

            else if (keyPressed->code == sf::Keyboard::Key::Enter) {
                if (phase == GamePhase::levelCleared) {
                    overlay_control.hide_text();
                    state.level++;
                    overlay_control.update_level(state.level);
                    state.lives = 3;
                    overlay_control.update_lives();

                    spaceship_control.setSpeed(400 + state.level*50);
                    alien_control.setMin(2.5-0.5*state.level);
                    alien_control.setMax(3.5-0.5*state.level);
                    alien_control.setSpeed(200+state.level*50);
                    alien_control.setSpeedControl(3 + state.level + 1);

                    start_next_level();
                    phase = GamePhase::playing;
                }   else if (phase == GamePhase::gameOver) {
                    overlay_control.hide_text();
                    reset_game();
                    phase = GamePhase::playing;
                 }
            }
        } 
    }
    return false;
}


void Game::update(float time_passed) {

    //halt the game if we are not playing
    if(phase != GamePhase::playing){
        return;
    }
    
    //Draw the GameOver screen
    if(alien_control.bottomReached()) {
        overlay_control.game_over();
        phase = GamePhase::gameOver;
        return; 
    };

    //check if the spaceship lost all his lives -> game over
    if(state.lives <= 0) {
       overlay_control.game_over();
       phase = GamePhase::gameOver;
       return; 
    }   


    //check if the spaceship hits an alien
  if(collisionAlien()) {
        state.alien_hits++;
        state.score += 10;
        overlay_control.update_score(state.score);
    }
    
    //check if the aliens hit the spaceship
   if (collisionSpaceship()) {
        state.spaceship_hits += 1;
        state.lives = std::max(0, state.lives -1);
        overlay_control.update_lives();
    }

    if(collisionPowerup()){
        powerup_control.delete_powerup();
        if(powerup_control.get_good_powerup()){
            spaceship_control.activate_good_powerup(5);
        }
        if(!powerup_control.get_good_powerup()){
            spaceship_control.activate_bad_powerup(5);
        }

    }
    //check if all Aliens are dead
    bool all_dead = true;
    for (auto& row : alien_control.alien_grid) {
        for (auto& a : row) {
            if (a.getAlive()) {
                all_dead = false;
                break;
            }
        }
        if (!all_dead) break;
    }
    if (all_dead){
        overlay_control.game_won();
        phase = GamePhase::levelCleared;
        return;
    }


    
    //update all positions
    spaceship_control.update_spaceship(time_passed);
    spaceship_control.update_shoot(time_passed);
    alien_control.update_aliens(time_passed);
    powerup_control.update_powerup(time_passed);
}

void Game::start_next_level(){
    alien_control.build_Aliengrid();
}

void Game::reset_game(){
    state = GameState{};
    overlay_control.update_lives();
    overlay_control.update_score(state.score);
    overlay_control.update_level(state.level);
    alien_control.build_Aliengrid();
}

void Game::draw() {
    window.clear();
    //draw the game elements
    game_layer.clear();
    spaceship_control.draw_spaceship();
    spaceship_control.draw_shoot();
    alien_control.draw_shoot();
    alien_control.draw_aliens();
    powerup_control.draw_powerup();
    
    //draw the overlay
    overlay_layer.clear();
    overlay_control.draw();

    //add all render targets to the window and draw them
    game_layer.draw();
    overlay_layer.draw();

    window.display();
}

bool Game::collisionAlien(){
    //check if an alien got hit
    bool alien_hit = false;

    // Iterating through all aliens:
    for(auto& row : alien_control.alien_grid){
        for(auto& alien : row){
            //Skip all dead aliens
            if(!alien.getAlive()){
                continue;
            }

            // Iterate through all shoots:
            for(auto& shot : spaceship_control.shoots){

                if(!shot.getActive()){
                    continue;
                }

                sf::FloatRect alienBounds = alien.getSprite().getGlobalBounds();
                sf::FloatRect shotBounds = shot.getSprite().getGlobalBounds();

                if(alienBounds.findIntersection(shotBounds)){

                    alien.take_damadge();
                    alien_hit = true;
                    shot.setActive(false);

                }
            }
        }
    }

    return alien_hit;
}

bool Game::collisionSpaceship(){
    //check if the spaceship got hit
    bool spaceship_hit = false;

        for(auto& shot : alien_control.shoots){

            if(!shot.getActive()){
                    continue;
            }

                sf::FloatRect spaceshipBounds = spaceship_control.spaceship.getSprite().getGlobalBounds();
                sf::FloatRect shotBounds = shot.getSprite().getGlobalBounds();

             if(spaceshipBounds.findIntersection(shotBounds)){

                    spaceship_hit = true;
                    shot.setActive(false);

            }
        }

    return spaceship_hit;
}

bool Game::collisionPowerup(){
    //check if an powerup is activated
    if(!powerup_control.get_powerup_active()){return false;}

                sf::FloatRect spaceshipBounds = spaceship_control.spaceship.getSprite().getGlobalBounds();
                sf::FloatRect powerupBounds = powerup_control.powerup.getSprite().getGlobalBounds();

             if(spaceshipBounds.findIntersection(powerupBounds)){
                    return true;
             }

    return false;
}
