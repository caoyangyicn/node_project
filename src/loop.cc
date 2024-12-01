// src/loop.cc
#include "loop.h"

namespace my_node {
    void init_event_system() {
        nodeLoop::getInstance().init_event_system();
    }

    void run_event_system() {
        nodeLoop::getInstance().run_event_system();
    }

    void close_event_system() {
        nodeLoop::getInstance().close_event_system();
    }
}