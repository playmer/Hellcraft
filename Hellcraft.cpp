/*
    NEET: Never Ever Enter There
    A game by Juliette Lavoie.
*/

// Project Headers.
#include "Application.hpp"

// Game Entry point.
int main(int argc, char* argv[]) {
    // Create our game and head into the loop.
    Game::Application myGame(1280, 720, "Hellcraft", "Assets/Icon.png");
    // Start game loop.
    myGame.applicationLoop();
    // Game over, exit after cleanup.
    return 0;
}