// Project Headers.
#include "Update.hpp"

namespace Engine {
    Update::Update() {
        init();
    }

    Update::~Update() {
        cleanup();
    }

    void Update::init() {

    }

    void Update::cleanup() {

    }

    void Update::pause() {

    }

    void Update::resume() {

    }

   Engine::Render Update::onEvent() {
        return Engine::Render {};
    }
}