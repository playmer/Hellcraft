#include <iostream>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    // Window size.
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    // Create the window.
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NEET");
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
    return EXIT_SUCCESS;
}