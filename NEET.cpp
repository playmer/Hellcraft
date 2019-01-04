/*
    NEET: Never Ever Enter There
    A game by Juliette Lavoie.
*/

// SFML Headers.
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
// Project Headers.
#include "FSM.hpp"
#include "Menu.hpp"

// Game Entry point.
int main(int argc, char* argv[]) {
    // Window size.
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    // Create the window with title and icon.
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NEET: Never Ever Enter There");
    sf::Image icon;
    if(!icon.loadFromFile("Assets/Icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // Create a new GSM and launch it.
    Engine::FSM<NEET::Menu> game(NEET::Menu{});
    // Start game loop.
    while(window.isOpen()) {
        // Used to capture events.
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            game.handleEvents();
            game.update();
        }
        window.clear();
        game.draw();
        window.display();
    }
    return EXIT_SUCCESS;
}