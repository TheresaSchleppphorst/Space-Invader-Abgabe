#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"

Game::Game() : window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    spaceship_control(game_layer)
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
        } 
    }
    return false;
}

void Game::update(float time_passed) {
    // TODO: update the game objects with the current time stamp

    //update the spaceships position
    spaceship_control.update_spaceship(time_passed);
}

void Game::draw() {
    window.clear();
    game_layer.clear();
    // TODO: add game elements to layer
    spaceship_control.draw_spaceship();
    
    game_layer.draw();
    

    window.display();
}
