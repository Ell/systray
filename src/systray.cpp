#include <thread>
#include <string>
#include <napi.h>

#if defined (_WIN32) || defined (_WIN64)
#define TRAY_WINAPI 1
#elif defined (__linux__) || defined (linux) || defined (__linux)
#define TRAY_APPINDICATOR 1
#elif defined (__APPLE__) || defined (__MACH__)
#define TRAY_APPKIT 1
#endif

#include "traywrapper.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  TrayWrapper::Init(env, exports);
  
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
