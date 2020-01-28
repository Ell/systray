#ifndef TRAYWRAPPER_H
#define TRAYWRAPPER_H

#include <napi.h>
#include "tray.h"

class TrayWrapper : public Napi::ObjectWrap<TrayWrapper> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    TrayWrapper(const Napi::CallbackInfo &info);

  private:
    static Napi::FunctionReference constructor;
    tray tray;

    void Start(const Napi::CallbackInfo &info);
    void Exit(const Napi::CallbackInfo &info);
    void Update(const Napi::CallbackInfo &info);
};

#endif