#include <v8.h>
#include <node.h>

using namespace v8;
using namespace node;

namespace {

struct ProfilerArguments {
  const int flags;
  const int tag;

  inline ProfilerArguments(const Arguments& args)
    : flags (args.Length() >= 1 ? args[0]->Uint32Value() : -1)
    , tag   (args.Length() >= 2 ? args[1]->Uint32Value() : 0)
  {
  }
};

Handle<Value> GC(const Arguments& args) {
  HandleScope scope;
  while (!V8::IdleNotification());
  return Undefined();
}

Handle<Value> Resume(const Arguments& args) {
  HandleScope scope;
  V8::ResumeProfiler();
  return Undefined();
}

Handle<Value> Pause(const Arguments& args) {
  HandleScope scope;
  V8::PauseProfiler();
  return Undefined();
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;

  target->Set(String::New("gc"), FunctionTemplate::New(GC)->GetFunction());
  target->Set(String::New("pause"), FunctionTemplate::New(Pause)->GetFunction());
  target->Set(String::New("resume"), FunctionTemplate::New(Resume)->GetFunction());

}

}
