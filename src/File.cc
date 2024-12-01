//
// Created by ubuntu on 24-12-1.
//

#include "File.h"

namespace my_node {
    namespace  File
    {
        static int count;
        void returnValue(const v8::FunctionCallbackInfo<v8::Value>& args){
            v8::Isolate* isolate = args.GetIsolate();
            if (args.Length() < 1 || !args[0]->IsFunction()) {
                isolate->ThrowException(v8::String::NewFromUtf8(isolate, "Argument must be a function", v8::NewStringType::kNormal).ToLocalChecked());
                return;
            }

            v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(args[0]);
            TimerData* data = new TimerData();
            data->isolate = isolate;
            data->jsFunction.Reset(isolate, jsFunction);

            uv_timer_t* timer = new uv_timer_t;
            timer->data = data;
            if (uv_timer_init(uv_default_loop(), timer) != 0) {
                std::cerr << "Failed to initialize timer" << std::endl;
                delete data;
                delete timer;
                return;
            }
            if (uv_timer_start(timer, TimerCallback, 0, 1000) != 0) {
                std::cerr << "Failed to start timer" << std::endl;
                delete data;
                delete timer;
                return;
            }
            std::cout << "Timer started, calling function every 1 second." << std::endl;

            // Run the event loop
            uv_run(uv_default_loop(), UV_RUN_DEFAULT);
            // uv_unref((uv_handle_t*)timer);
        }

        void TimerCallback(uv_timer_t* handle) {
            TimerData* data = static_cast<TimerData*>(handle->data);
            if (!data) {
                std::cerr << "TimerData is null" << std::endl;
                return;
            }
            v8::Isolate* isolate = data->isolate;
            v8::HandleScope handleScope(isolate);
            v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::New(isolate, data->jsFunction);
            count++;
            v8::Local<v8::Number> arg = v8::Number::New(isolate, count);
            v8::Local<v8::Value> argv[1] = { arg };
            v8::MaybeLocal<v8::Value> result = jsFunction->Call(isolate->GetCurrentContext(), v8::Null(isolate), 1, argv).ToLocalChecked();
            if (result.IsEmpty()) {
                std::cerr << "Failed to call JavaScript function" << std::endl;
            }
        }

        void Initialize(v8::Isolate * isolate, v8::Local<v8::Object> global, v8::Local<v8::Context> context){
            v8::Local<v8::ObjectTemplate> file = v8::ObjectTemplate::New(isolate);
            setMethod(isolate, file, "returnValue", returnValue);
            global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "File", \
              NewStringType::kNormal).ToLocalChecked(), \
              file->NewInstance(isolate->GetCurrentContext()).ToLocalChecked());
        }
    }
} // my_node