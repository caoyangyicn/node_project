// src/loop.h
#ifndef EVENT_H
#define EVENT_H


#include "uv.h"

const int MAX_EVENT_SIZE = 100;

namespace my_node {

    class nodeLoop {
    public:
        static nodeLoop& getInstance() {
            static nodeLoop instance;
            return instance;
        }

        void init_event_system() {
            uv_loop_init(loop);
        }

        void run_event_system() {
            uv_run(loop, UV_RUN_DEFAULT);
        }

        void close_event_system() {
            uv_loop_close(loop);
        }

        uv_loop_t* getLoop() {
            return loop;
        }

    private:
        nodeLoop() = default;
        ~nodeLoop() = default;
        nodeLoop(const nodeLoop&) = delete;
        nodeLoop& operator=(const nodeLoop&) = delete;

        uv_loop_t* loop;
    };
}

#endif // EVENT_H