#include <node.h>
#include <v8.h>
#include <node_buffer.h>
#include "ecrypt-sync.h"
#include <string>
#include <iostream>
#include "palringo-auth.hpp"

using namespace v8;

void Method(const v8::FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    char* authMessage = (char*) node::Buffer::Data(args[0]->ToObject());
    char* password = (char*) node::Buffer::Data(args[1]->ToObject());
    size_t len = args[2]->NumberValue();

    // Auth
    unsigned char authMsg[24];
    bzero(authMsg, 25);

    std::string s2(authMessage);
    int pos = s2.find("\r\n\r\n");
    pos+=4;

    size_t t = 0;
    while (t < 24) {
        authMsg[t] = authMessage[pos + t];
        t++;
    }

    PalAuth::Salsa20::authenticate
    (authMsg, (unsigned char*)password, len, (unsigned char*) node::Buffer::Data(args[3]->ToObject()));

    // args.GetReturnValue().Set(String::NewFromUtf8(isolate, (char*)c));
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "authenticate"),
      FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(PalAuth, Init)