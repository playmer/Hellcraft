#pragma once

/*
Implements a Menu which is based off the State abstract class.
*/

// Project Headers.
#include "FSM.hpp"
// Wrapper Headers.
#include "Window.hpp"
#include "Event.hpp"
#include "Clock.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Animation.hpp"

namespace Game {
    template <typename ...T>
    class FSM;

    class Menu {
    public:
        inline Menu();
        inline ~Menu();

        inline void init();
        inline void cleanup();

        inline void pause();
        inline void resume();

        template <typename FSM> 
        void handleEvents(FSM* p_fsm, const Engine::Event& p_event);
        template <typename FSM> 
        void update(FSM* p_fsm, const Engine::Clock& p_clock);
        template <typename FSM> 
        void draw(FSM* p_fsm, Engine::Window* p_window);

    private:
        Engine::Texture m_texture;
        Engine::Sprite m_sprite;
        Engine::Animation m_animation;
    };

    Menu::Menu() {
        Logger::log(INFO, "Menu constructor called!");
    }

    Menu::~Menu() {
        Logger::log(INFO, "Menu destroyed!");
    }

    void Menu::init() {
        Logger::log(INFO, "Initializing menu.");
        m_texture.loadFile("Assets/Tileset.png", 16, 368, 32, 32);
        m_sprite.loadTexture(m_texture);
        m_animation.init(m_texture, false, true);
        m_animation.setFrames(16, 368, 256, 32, 32, 32);
    }

    void Menu::cleanup() {
        Logger::log(INFO, "Cleaning up menu.");
    }

    void Menu::pause() {

    }

    void Menu::resume() {

    }

    template <typename FSM> 
    void Menu::handleEvents(FSM* p_fsm, const Engine::Event& p_event) {
        
    }

    template <typename FSM> 
    void Menu::update(FSM* p_fsm, const Engine::Clock& p_clock) {

    }

    template <typename FSM> 
    void Menu::draw(FSM* p_fsm, Engine::Window* p_window) {
        p_window->getWindow().draw(m_sprite.getSprite());
    }
}