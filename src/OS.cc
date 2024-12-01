//
// Created by ubuntu on 24-12-1.
//

#include "OS.h"

namespace my_node {
    namespace OS
    {
        static void GetHostname(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();
            char buf[UV_MAXHOSTNAMESIZE];
            size_t size = sizeof(buf);
            int r = uv_os_gethostname(buf, &size);

            if (r != 0) {
                if (args.Length() > 0)
                {
                    isolate->ThrowException(v8::String::NewFromUtf8(isolate, "The parameter must be null", v8::NewStringType::kNormal).ToLocalChecked());
                    return;
                }

                return args.GetReturnValue().SetUndefined();
            }

            args.GetReturnValue().Set(
                String::NewFromUtf8(isolate, buf).ToLocalChecked());
        }
        static void GetOSInformation(const FunctionCallbackInfo<Value>& args) {
            uv_utsname_t info;
            int err = uv_os_uname(&info);
            Isolate *isolate = args.GetIsolate();
            if (err != 0) {
                isolate->ThrowException(v8::String::NewFromUtf8(isolate, "The parameter must be null", v8::NewStringType::kNormal).ToLocalChecked());
                return args.GetReturnValue().SetUndefined();
            }

            // [sysname, version, release, machine]
            Local<Value> osInformation[] = {
                String::NewFromUtf8(isolate, info.sysname).ToLocalChecked(),
                String::NewFromUtf8(isolate, info.version).ToLocalChecked(),
                String::NewFromUtf8(isolate, info.release).ToLocalChecked(),
                String::NewFromUtf8(isolate, info.machine).ToLocalChecked()};

            args.GetReturnValue().Set(Array::New(isolate,
                                                 osInformation,
                                                 arraysize(osInformation)));
        }
        static void GetCPUInfo(const FunctionCallbackInfo<Value>& args) {
            Isolate* isolate = args.GetIsolate();

            uv_cpu_info_t* cpu_infos;
            int count;

            int err = uv_cpu_info(&cpu_infos, &count);
            if (err)
                return;

            // It's faster to create an array packed with all the data and
            // assemble them into objects in JS than to call Object::Set() repeatedly
            // The array is in the format
            // [model, speed, (5 entries of cpu_times), model2, speed2, ...]
            std::vector<Local<Value>> result;
            result.reserve(count * 7);
            for (int i = 0; i < count; i++) {
                uv_cpu_info_t* ci = cpu_infos + i;
                result.emplace_back(OneByteString(isolate, ci->model));
                result.emplace_back(Number::New(isolate, ci->speed));
                result.emplace_back(
                    Number::New(isolate, static_cast<double>(ci->cpu_times.user)));
                result.emplace_back(
                    Number::New(isolate, static_cast<double>(ci->cpu_times.nice)));
                result.emplace_back(
                    Number::New(isolate, static_cast<double>(ci->cpu_times.sys)));
                result.emplace_back(
                    Number::New(isolate, static_cast<double>(ci->cpu_times.idle)));
                result.emplace_back(
                    Number::New(isolate, static_cast<double>(ci->cpu_times.irq)));
            }

            uv_free_cpu_info(cpu_infos, count);
            args.GetReturnValue().Set(Array::New(isolate, result.data(), result.size()));
        }

        void Initialize(v8::Isolate * isolate, v8::Local<v8::Object> global, v8::Local<v8::Context> context){
            v8::Local<v8::ObjectTemplate> OS = v8::ObjectTemplate::New(isolate);
            setMethod(isolate, OS, "getHostname", GetHostname);
            setMethod(isolate, OS, "getOSInformation", GetOSInformation);
            setMethod(isolate, OS, "getCPUInfo", GetCPUInfo);
            global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "OS", \
              NewStringType::kNormal).ToLocalChecked(), \
              OS->NewInstance(isolate->GetCurrentContext()).ToLocalChecked());
        }
    }
} // my_node