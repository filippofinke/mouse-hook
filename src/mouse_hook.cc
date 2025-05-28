#include "macos/mouse_hook_mac.h"

// Module initialization
napi_value Init(napi_env env, napi_value exports) {
  napi_property_descriptor desc[] = {
      {"startListening", nullptr, mouse_hook::StartListening, nullptr, nullptr,
       nullptr, napi_default, nullptr},
      {"stopListening", nullptr, mouse_hook::StopListening, nullptr, nullptr,
       nullptr, napi_default, nullptr},
      {"isListening", nullptr, mouse_hook::IsListening, nullptr, nullptr,
       nullptr, napi_default, nullptr}};

  napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
