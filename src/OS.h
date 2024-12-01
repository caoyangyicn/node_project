//
// Created by ubuntu on 24-12-1.
//

#ifndef OS_H
#define OS_H
#include "util.h"

#include "uv.h"

namespace my_node {

namespace  OS {
    static void GetHostname(const FunctionCallbackInfo<Value>& args);
    static void GetOSInformation(const FunctionCallbackInfo<Value>& args);
    static void GetCPUInfo(const FunctionCallbackInfo<Value>& args);
    void Initialize(v8::Isolate * isolate, v8::Local<v8::Object> global, v8::Local<v8::Context> context);
};

} // my_node

#endif //OS_H
