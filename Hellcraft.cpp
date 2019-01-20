/*
    Hellcraft.
    An excerise in implementing a game and engine in an extensive dungeoncrawler.
*/

// Standard Headers.
#include <chrono>
// Engine Headers.
#include "Application.hpp"
#include "Log.hpp"
// Game Headers.
#include "RNG.hpp"

// Game Entry point.
int main(int argc, char* argv[]) {
    // Create logging system and launch it.
    Logger::startLog("log.txt");
    // Seed RNG engine.
    Game::g_rng.seed(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    // Create our game and head into the loop.
    Logger::log(INFO, "Creating instance of application class to create game.");
    Game::Application myGame(1280, 720, "Hellcraft", "Assets/Icon.png");
    // Start game loop.
    Logger::log(INFO, "Started application loop.");
    myGame.applicationLoop();
    // Game over, exit after cleanup.
    return 0;
}