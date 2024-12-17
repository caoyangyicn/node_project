
#include "util.h"
#include "console.h"
#include "File.h"
#include "OS.h"
using namespace v8;
namespace my_node
{
        std::string ToString(Local<Value> value) {
            Isolate* isolate = Isolate::GetCurrent();
            String::Utf8Value utf8(isolate, value);
            return *utf8 ? *utf8 : "null";
        }
        // 设置对象的属性，属性为函数
        void setMethod(Isolate *isolate,
                        Local<ObjectTemplate>
                        recv, const char *name,
                        FunctionCallback callback) {
            recv->Set(String::NewFromUtf8(isolate, name,
                NewStringType::kNormal).ToLocalChecked(),
                FunctionTemplate::New(isolate, callback));
        }

        void register_builtins(Isolate * isolate, Local<Object> global, Local<Context> context) {
            MOLEULES_LIST(MV);
        }

        void generateErrorMessage(Isolate* isolate, char* msg)
        {
            v8::Local<v8::String> errorMessage = v8::String::NewFromUtf8(isolate, msg).ToLocalChecked();
            v8::Local<v8::Value> error = v8::Exception::Error(errorMessage);
            isolate->ThrowException(error);
        }
        std::string makeUTF8String(Isolate *isolate, v8::Local<v8::Value> value)
        {
            v8::String::Utf8Value path(isolate, value);
            return *path ? *path : "null";
        }
}


 