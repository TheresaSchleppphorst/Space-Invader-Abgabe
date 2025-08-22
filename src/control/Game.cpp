#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include <algorithm>

Game::Game() : window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    overlay_layer(window),
    overlay_control(overlay_layer, state),
    spaceship_control(game_layer),
    alien_control(game_layer)
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
             // shooting with space bar:
            else if (keyPressed->code == sf::Keyboard::Key::Space) {
                 spaceship_control.space_bar_pressed();
            }
        } 
    }
    return false;
}

void Game::update(float time_passed) {
    spaceship_control.update_spaceship(time_passed);
    spaceship_control.update_shoot(time_passed);
    alien_control.update_aliens(time_passed);
    

    //check if an alien got hit
   /** if(collision_alien) {
        state.alien_hits++;
        state.score += 10;
        overlay_control.update_score(state.score);
    }
    
    //check if the aliens hit the spaceship
   if (spaceship_got_hit) {
        state.spaceship_hits += 1;
        state.lives = std::max(0, state.lives -1);
        overlay_control.update_lives(state.lives);
    }
    */

    //check if level upgrade is necessary
    if (state.game_won) {
        state.level++;
        overlay_control.update_level(state.level);
        state.game_won = false;
    }

    //check if the spaceship lost all his lives -> game over
    if(state.lives <= 0) {
       overlay_control.game_over();
       return; // should stop everything
    }   
    //update the spaceships position
    spaceship_control.update_spaceship(time_passed);
}

void Game::draw() {
    window.clear();
    //draw the game elements
    game_layer.clear();
    spaceship_control.draw_spaceship();
    spaceship_control.draw_shoot();
    alien_control.draw_aliens();
    
    //draw the overlay
    overlay_layer.clear();
    overlay_control.draw();

    //add all render targets to the window and draw them
    game_layer.draw();
    overlay_layer.draw();

    window.display();
}
