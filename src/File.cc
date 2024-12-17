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
            uv_unref((uv_handle_t*)timer);
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



        static void ReadFileUtf8(const FunctionCallbackInfo<Value>& args) {
            Environment* env = Environment::GetInstance();
            auto isolate = env->isolate();

            int flags = args[1].As<Int32>()->Value();

            uv_file file;
            uv_fs_t req;

            bool is_fd = args[0]->IsInt32();

            if (is_fd) {
                file = args[0].As<Int32>()->Value();
            }
            else
            {
                v8::String::Utf8Value path(isolate, args[0]);
                std::string result = *path ? *path : "null";
                if (flags == 0)
                {
                    flags = (UV_FS_O_RDONLY | UV_FS_O_WRONLY | UV_FS_O_RDWR);
                }
                file = uv_fs_open(nullptr, &req, result.c_str(), flags, 0666, nullptr);
                if (req.result < 0) {
                    uv_fs_req_cleanup(&req);
                    generateErrorMessage(isolate, "cannot open the file");
                    return;
                }
            }

            std::string result{};
            char buffer[8192];
            uv_buf_t buf = uv_buf_init(buffer, sizeof(buffer));

            while (true) {
                auto r = uv_fs_read(nullptr, &req, file, &buf, 1, -1, nullptr);
                if (req.result < 0) {
                    uv_fs_req_cleanup(&req);
                    generateErrorMessage(isolate, "read error!");
                    return;
                }
                if (r <= 0) {
                    break;
                }
                result.append(buf.base, r);
            }
            v8::Local<v8::String> val = v8::String::NewFromUtf8(isolate, result.c_str(), v8::NewStringType::kNormal).ToLocalChecked();
            args.GetReturnValue().Set(val);
        }

        static void ExistsSync(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();
            std::string path;
            if (args[0]->IsString())
            {
                path = makeUTF8String(isolate, args[0]);
            }
            else
            {
                generateErrorMessage(isolate, "Wrong Args!");
                return;
            }
            uv_fs_t req;
            int err = uv_fs_access(nullptr, &req, path.c_str(), 0, nullptr);
            args.GetReturnValue().Set(err == 0);
        }

        void Initialize(v8::Isolate * isolate, v8::Local<v8::Object> global, v8::Local<v8::Context> context){
            v8::Local<v8::ObjectTemplate> file = v8::ObjectTemplate::New(isolate);
            setMethod(isolate, file, "returnValue", returnValue);
            setMethod(isolate, file, "readFileUtf8", ReadFileUtf8);
            setMethod(isolate, file, "existsSync", ExistsSync);
            global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "File", \
              NewStringType::kNormal).ToLocalChecked(), \
              file->NewInstance(isolate->GetCurrentContext()).ToLocalChecked());
        }
    }
} // my_node