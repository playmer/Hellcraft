// Project Headers.
#include "Render.hpp"

namespace Engine {
    Render::Render() {
        init();
    }

    Render::~Render() {
        cleanup();
    }

    void Render::init() {

    }

    void Render::cleanup() {

    }

    void Render::pause() {

    }

    void Render::resume() {

    }

    Engine::IO Render::onEvent() {
        return Engine::IO {};
    }
}