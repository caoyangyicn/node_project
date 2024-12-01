#pragma once
#include <fcntl.h>
#include <unistd.h>
#include "v8.h"
#include "include/libplatform/libplatform.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-isolate.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"
#include <cstddef>
#include <iostream>

using namespace v8;

template <typename T, size_t N>
constexpr size_t arraysize(const T (&)[N]) {
    return N;
}

namespace my_node
{

        #define MV(module) \
        module::Initialize(isolate, global, context);


        #define MOLEULES_LIST(V) \
        V(Console1)              \
        V(File)                  \
        V(OS)

        void setMethod(Isolate *isolate,
                        Local<ObjectTemplate>
                        recv, const char *name,
                        FunctionCallback callback);

        void register_builtins(Isolate * isolate, Local<Object> global, Local<Context> context);
        std::string ToString(Local<Value> value);
        inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate,
                                           const char* data,
                                           int length) {
            return v8::String::NewFromOneByte(isolate,
                                              reinterpret_cast<const uint8_t*>(data),
                                              v8::NewStringType::kNormal,
                                              length).ToLocalChecked();
        }

        // Convenience wrapper around v8::String::NewFromOneByte().
        inline v8::Local<v8::String> OneByteString(v8::Isolate* isolate,
                                               const char* data,
                                               int length = -1);


}
