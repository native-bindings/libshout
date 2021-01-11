#include "Shout.h"

NAN_MODULE_INIT(Shout::Init) {
    shout_init();

    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Shout").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    Nan::SetPrototypeMethod(tpl, "setHost", SetHost);
    Nan::SetPrototypeMethod(tpl, "setProtocol", SetProtocol);
    Nan::SetPrototypeMethod(tpl, "setFormat", SetFormat);
    Nan::SetPrototypeMethod(tpl, "setUser", SetUser);
    Nan::SetPrototypeMethod(tpl, "setMount", SetMount);
    Nan::SetPrototypeMethod(tpl, "sync", Sync);
    Nan::SetPrototypeMethod(tpl, "setPassword", SetPassword);
    Nan::SetPrototypeMethod(tpl, "setPort", SetPort);
    Nan::SetPrototypeMethod(tpl, "open", Open);
    Nan::SetPrototypeMethod(tpl, "send", Send);
    Nan::SetPrototypeMethod(tpl, "close", Close);
    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Shout").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

std::string Shout::getString(Nan::NAN_METHOD_ARGS_TYPE& info, uint32_t i) {
    auto str = Nan::To<v8::String>(info[i]).ToLocalChecked();
    auto length = Nan::Utf8String(str).length();
    char host[length + 1];

    str->WriteUtf8(Nan::GetCurrentContext()->GetIsolate(), host, length);

    host[length] = 0;

    std::string out(host);

    return out;
}

Shout::Shout() {
    id = shout_new();
    if(!id) {
        Nan::ThrowError("Failed to construct shout instance");
    }
}
Shout::~Shout() {
    shout_free(id);
}
bool Shout::open() {
    return shout_open(id) == SHOUTERR_SUCCESS;
}
bool Shout::send(unsigned char* data, size_t len) {
    return shout_send(id, data, len) == SHOUTERR_SUCCESS;
}
void Shout::sync() {
    shout_sync(id);
}
bool Shout::setHost(const char* host) {
    return shout_set_host(id, host) == SHOUTERR_SUCCESS;
}
bool Shout::setPassword(const char* pass) {
    return shout_set_password(id, pass) == SHOUTERR_SUCCESS;
}
bool Shout::setMount(const char* mount) {
    return shout_set_mount(id, mount) == SHOUTERR_SUCCESS;
}
bool Shout::setUser(const char* username) {
    return shout_set_user(id, username) == SHOUTERR_SUCCESS;
}
bool Shout::close() {
    return shout_close(id) == SHOUTERR_SUCCESS;
}
bool Shout::setProtocol(unsigned int protocol) {
    return shout_set_protocol(id, protocol) == SHOUTERR_SUCCESS;
}
bool Shout::setFormat(unsigned int format) {
    return shout_set_format(id, format) == SHOUTERR_SUCCESS;
}
bool Shout::setPort(unsigned short port) {
    return shout_set_port(id, port) == SHOUTERR_SUCCESS;
}
size_t Shout::getInt32(Nan::NAN_METHOD_ARGS_TYPE& info, uint32_t i) {
    return Nan::To<v8::Number>(info[i]).ToLocalChecked()->Int32Value(Nan::GetCurrentContext()).ToChecked();
}
NAN_METHOD(Shout::SetHost) {
    if(!info[0]->IsString()) {
        Nan::ThrowError("First argument must be a string");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setHost(getString(info, 0).c_str())) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::Sync) {
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    shout->sync();
}
NAN_METHOD(Shout::Send) {
    if(!info[0]->IsArrayBuffer()) {
        Nan::ThrowError("First argument must be a string");
        return;
    }
    auto buffer = v8::Local<v8::ArrayBuffer>::Cast(info[0]);
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    auto data = static_cast<unsigned char*>(buffer->GetContents().Data());

    if(!shout->send(data, buffer->ByteLength())) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::Open) {
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->open()) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::SetUser) {
    if(!info[0]->IsString()) {
        Nan::ThrowError("First argument must be a string");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setUser(getString(info, 0).c_str())) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::SetFormat) {
    if(!info[0]->IsNumber()) {
        Nan::ThrowError("First argument must be a number");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setFormat(getInt32(info, 0))) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::SetPassword) {
    if(!info[0]->IsString()) {
        Nan::ThrowError("First argument must be a string");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setPassword(getString(info, 0).c_str())) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::SetMount) {
    if(!info[0]->IsString()) {
        Nan::ThrowError("First argument must be a string");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setMount(getString(info, 0).c_str())) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::SetProtocol) {
    if(!info[0]->IsNumber()) {
        Nan::ThrowError("First argument must be a number");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setProtocol(getInt32(info, 0))) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::SetPort) {
    if(!info[0]->IsNumber()) {
        Nan::ThrowError("First argument must be a number");
        return;
    }
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->setPort(getInt32(info, 0))) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::Close) {
    auto* shout = Nan::ObjectWrap::Unwrap<Shout>(info.Holder());

    if(!shout->close()) {
        Nan::ThrowError(shout_get_error(shout->id));
    }
}
NAN_METHOD(Shout::New) {
    if(!info.IsConstructCall()) {
        Nan::ThrowError("Shout class must be instantiate using new");
        return;
    }
    auto* obj = new Shout();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

NODE_MODULE(shout, Shout::Init)
