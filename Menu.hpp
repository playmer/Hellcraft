#pragma once

/*
Implements a Menu which is based off the State abstract class.
*/

// Standard Headers.
#include <string>
// Project Headers.
#include "FSM.hpp"
#include "Window.hpp"
#include "Event.hpp"
#include "Clock.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Animation.hpp"
#include "Manager.hpp"

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
        void handleEvents(FSM& p_fsm, Engine::Event& p_event);
        template <typename FSM> 
        void update(FSM& p_fsm, Engine::Clock& p_clock);
        template <typename FSM> 
        void draw(FSM& p_fsm, Engine::Window& p_window);

    private:
        Engine::Animation m_animation;
        Engine::Manager m_resourceManager;
    };

    Menu::Menu() {
        Logger::log(INFO, "Menu constructor called!");
    }

    Menu::~Menu() {
        Logger::log(INFO, "Menu destroyed!");
    }

    void Menu::init() {
        Logger::log(INFO, "Initializing menu.");
        m_resourceManager.addResourceType<Engine::Texture>(&Engine::Texture::loadTexture);
        m_resourceManager.addResource<Engine::Texture>("Tileset", "Assets/Tileset.png");
        m_animation.init(*m_resourceManager.getResource<Engine::Texture>("Tileset"), 7.5);
        m_animation.cutFrames(16, 364, 128, 36, 32, 36);
    }

    void Menu::cleanup() {
        Logger::log(INFO, "Cleaning up menu.");
    }   

    void Menu::pause() {

    }

    void Menu::resume() {

    }

    template <typename FSM>     
    void Menu::handleEvents(FSM& p_fsm, Engine::Event& p_event) {
        if(p_event.getEvent().type == sf::Event::KeyPressed && p_event.getEvent().key.code == sf::Keyboard::P) {
            m_animation.pause();
        }
        if(p_event.getEvent().type == sf::Event::KeyPressed && p_event.getEvent().key.code == sf::Keyboard::R) {
            m_animation.play();
        }
    }

    template <typename FSM> 
    void Menu::update(FSM& p_fsm, Engine::Clock& p_clock) {
        m_animation.update(p_clock);
    }

    template <typename FSM>     
    void Menu::draw(FSM& p_fsm, Engine::Window& p_window) {
        p_window.getWindow().draw(m_animation);
    }
}