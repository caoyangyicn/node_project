//
// Created by ubuntu on 24-12-8.
//
#ifndef ENVIROMENT_H
#define ENVIROMENT_H
#include "util.h"
#include "uv.h"



namespace my_node {
    class Environment {
    public:
        static Environment* GetInstance(uv_loop_t* event_loop = nullptr, Isolate* isolate = nullptr) {
            static Environment instance(event_loop, isolate);
            return &instance;
        }

        v8::Isolate* isolate() const {
            return isolate_;
        }


    private:
        Environment(uv_loop_t* event_loop, Isolate* isolate)
            : isolate_(isolate), timer_base_(uv_now(event_loop)) {}
        v8::Isolate* const isolate_;
        const uint64_t timer_base_;

    };
} // my_node

#endif //ENVIROMENT_H
