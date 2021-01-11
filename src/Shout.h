#pragma once

#include <nan.h>
#include <shout/shout.h>

class Shout : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Init);
private:
    shout_t* id;
    Shout();
    ~Shout();
    bool open();
    bool send(unsigned char* data, size_t len);
    void sync();
    bool setHost(const char* host);
    bool setPassword(const char* pass);
    bool setMount(const char* mount);
    bool setUser(const char* username);
    bool close();
    bool setProtocol(unsigned int protocol);
    bool setFormat(unsigned int format);
    bool setPort(unsigned short port);
    static std::string getString(Nan::NAN_METHOD_ARGS_TYPE& info, uint32_t i);
    static size_t getInt32(Nan::NAN_METHOD_ARGS_TYPE& info, uint32_t i);
    static NAN_METHOD(SetHost);
    static NAN_METHOD(Sync);
    static NAN_METHOD(Send);
    static NAN_METHOD(Open);
    static NAN_METHOD(SetUser);
    static NAN_METHOD(SetFormat);
    static NAN_METHOD(SetPassword);
    static NAN_METHOD(SetMount);
    static NAN_METHOD(SetProtocol);
    static NAN_METHOD(SetPort);
    static NAN_METHOD(Close);
    static NAN_METHOD(New);
    static inline Nan::Persistent<v8::Function>&constructor() {
        static Nan::Persistent<v8::Function> my_constructor;
        return my_constructor;
    }
};
