#ifndef MOUSE_HOOK_MAC_H
#define MOUSE_HOOK_MAC_H

#include <node_api.h>

namespace mouse_hook {

// Mouse event data structure
struct MouseEventData {
  int button; // 0 = left, 1 = right, 2 = other
  double x;
  double y;
};

// Thread management for run loop
void *RunEventLoop(void *arg);
void StopEventLoop();

// Start listening for mouse events
napi_value StartListening(napi_env env, napi_callback_info info);

// Stop listening for mouse events
napi_value StopListening(napi_env env, napi_callback_info info);

// Check if currently listening
napi_value IsListening(napi_env env, napi_callback_info info);

} // namespace mouse_hook

#endif // MOUSE_HOOK_MAC_H
