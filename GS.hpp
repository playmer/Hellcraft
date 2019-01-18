#pragma once

/*
Implements a Game which is based off the State abstract class.
*/

// Standard Headers.
#include <string>
// Engine Headers.
#include "Animation.hpp"
#include "Clock.hpp"
#include "Event.hpp"
#include "FSM.hpp"
#include "Manager.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Window.hpp"
// Game Headers.
#include "Menu.hpp"
#include "Level.hpp"

namespace Game {
    template <typename ...T>
    class FSM;

    class Menu;

    class GS {
    public:
        inline GS();
        inline ~GS();

        inline void init();
        inline void cleanup();

        inline void pause();
        inline void resume();

        template <typename FSM> 
        void handleEvents(FSM& p_fsm, Engine::Event& p_event);
        template <typename FSM> 
        void update(FSM& p_fsm, Engine::Clock& p_clock);
        template <typename FSM> 
        void draw(FSM& p_fsm, Engine::Window& p_window);

    private:
        Engine::Animation m_animation;
        Engine::Manager m_resourceManager;
        Game::Level m_level;
    };

    GS::GS() : m_level {} {
        Logger::log(INFO, "Game state constructor called!");
    }

    GS::~GS() {
        Logger::log(INFO, "Game state destroyed!");
    }

    void GS::init() {
        Logger::log(INFO, "Initializing game.");
        m_resourceManager.addResourceType<Engine::Texture>(&Engine::Texture::loadTexture);
        m_resourceManager.addResource<Engine::Texture>("Tileset", "Assets/Tileset.png");
        m_animation.init(*m_resourceManager.getResource<Engine::Texture>("Tileset"), 7.5);
        m_animation.cutFrames(16, 270, 128, 34, 32, 34);
    }

    void GS::cleanup() {
        Logger::log(INFO, "Cleaning up game state.");
    }   

    void GS::pause() {
        Logger::log(INFO, "Game paused!");
    }

    void GS::resume() {
        Logger::log(INFO, "Game resumed!");
    }

    template <typename FSM>     
    void GS::handleEvents(FSM& p_fsm, Engine::Event& p_event) {
        if(p_event.getEvent().type == sf::Event::KeyPressed && p_event.getEvent().key.code == sf::Keyboard::P) {
            m_animation.pause();
        }
        if(p_event.getEvent().type == sf::Event::KeyPressed && p_event.getEvent().key.code == sf::Keyboard::R) {
            m_animation.play();
        }
        if(p_event.getEvent().type == sf::Event::KeyPressed && p_event.getEvent().key.code == sf::Keyboard::Escape) {
            p_fsm.changeState(Game::Menu{});
        }
    }

    template <typename FSM> 
    void GS::update(FSM& p_fsm, Engine::Clock& p_clock) {
        m_animation.update(p_clock);
    }

    template <typename FSM>     
    void GS::draw(FSM& p_fsm, Engine::Window& p_window) {
        p_window.getWindow().draw(m_animation);
    }
}