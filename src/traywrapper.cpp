
#include "traywrapper.h"
#include "tray.h"

Napi::Object TrayWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "TrayWrapper", {
    InstanceMethod("Start", &TrayWrapper::Start),
    InstanceMethod("Exit", &TrayWrapper::Exit),
    InstanceMethod("Update", &TrayWrapper::Update)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Tray", func);

  return exports;
}

TrayWrapper::TrayWrapper(const Napi::CallbackInfo &info)
  : Napi::ObjectWrap<TrayWrapper>(info) {
    Napi::Env env = info.Env();

    struct tray tray = {};

    tray.icon = "icon.png";

    std::vector<tray_menu> menu = {
      {"test1", 0, 0, NULL, NULL},
      {"test2", 0, 0, NULL, NULL}
    };

    tray.menu = menu.data();

    this->tray = tray;
  }

Napi::FunctionReference TrayWrapper::constructor;

void TrayWrapper::Start(const Napi::CallbackInfo &info) {
  tray_init(&this->tray);
  while (tray_loop(1) == 0);
  tray_exit();
}

void TrayWrapper::Exit(const Napi::CallbackInfo &info) {
  tray_exit();
}

void TrayWrapper::Update(const Napi::CallbackInfo &info) {}
