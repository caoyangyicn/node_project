
#include "console.h"
#include "util.h"

using namespace std;
namespace my_node
{
    namespace Console1
    {
        void Log(const FunctionCallbackInfo<Value> &args) {
            Isolate* isolate = args.GetIsolate();
            v8::String::Utf8Value str(isolate, args[0]);
            printf("%s\n", *str);
        }

        void Initialize(Isolate * isolate, Local<Object> global, Local<Context> context){
            Local<ObjectTemplate> Console1 = ObjectTemplate::New(isolate);
            setMethod(isolate, Console1, "log", Console1::Log);
            global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "console", \
              NewStringType::kNormal).ToLocalChecked(), \
              Console1->NewInstance(isolate->GetCurrentContext()).ToLocalChecked());
        }
    }
}

