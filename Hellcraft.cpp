/*
    NEET: Never Ever Enter There
    A game by Juliette Lavoie.
*/

// Engine Headers.
#include "Application.hpp"
#include "Log.hpp"

// Game Entry point.
int main(int argc, char* argv[]) {
    // Create logging system and launch it.
    Logger::startLog("log.txt");
    // Create our game and head into the loop.
    Logger::log(INFO, "Creating instance of application class to create game.");
    Game::Application myGame(1280, 720, "Hellcraft", "Assets/Icon.png");
    // Start game loop.
    Logger::log(INFO, "Started application loop.");
    myGame.applicationLoop();
    // Game over, exit after cleanup.
    return 0;
}