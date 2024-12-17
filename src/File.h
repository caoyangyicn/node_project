//
// Created by ubuntu on 24-12-1.
//

#ifndef FILE_H
#define FILE_H
#include "v8.h"
#include "include/v8-context.h"
#include "include/v8-local-handle.h"
#include "uv.h"
#include "util.h"
#include "loop.h"
#include <iostream>
#include "Environment.h"

namespace my_node {

namespace File {
    struct TimerData {
        v8::Persistent<v8::Function> jsFunction;
        v8::Isolate* isolate;
    };
    void TimerCallback(uv_timer_t* handle);
    void returnValue(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ReadFileUtf8(const FunctionCallbackInfo<Value>& args);
    void Initialize(v8::Isolate * isolate, v8::Local<v8::Object> global, v8::Local<v8::Context> context);
    static void ExistsSync(const FunctionCallbackInfo<Value>& args);
};

} // my_node

#endif //FILE_H
