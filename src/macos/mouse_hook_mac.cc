#include "mouse_hook_mac.h"
#include <CoreGraphics/CoreGraphics.h>
#include <iostream>
#include <pthread.h>

namespace mouse_hook {

static CFMachPortRef eventTap = nullptr;
static CFRunLoopSourceRef runLoopSource = nullptr;
static napi_threadsafe_function tsfn = nullptr;
static pthread_t runLoopThread;
static CFRunLoopRef runLoop = nullptr;
static bool shouldStopRunLoop = false;

// Event tap callback
CGEventRef mouseEventCallback(CGEventTapProxy proxy, CGEventType type,
                              CGEventRef event, void *refcon) {
  if (type == kCGEventLeftMouseDown || type == kCGEventRightMouseDown ||
      type == kCGEventOtherMouseDown) {
    CGPoint location = CGEventGetLocation(event);

    MouseEventData *data = new MouseEventData();
    data->x = location.x;
    data->y = location.y;

    switch (type) {
    case kCGEventLeftMouseDown:
      data->button = 0;
      break;
    case kCGEventRightMouseDown:
      data->button = 1;
      break;
    case kCGEventOtherMouseDown:
      data->button = 2;
      break;
    default:
      data->button = -1;
      break;
    }

    if (tsfn != nullptr) {
      napi_call_threadsafe_function(tsfn, data, napi_tsfn_blocking);
    }
  }

  return event;
}

// Thread function to run the event loop
void *RunEventLoop(void *arg) {
  runLoop = CFRunLoopGetCurrent();

  // Add the run loop source to this thread's run loop
  CFRunLoopAddSource(runLoop, runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  // Run the loop until stopped
  while (!shouldStopRunLoop) {
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);
  }

  // Cleanup will be done in StopEventLoop
  runLoop = nullptr;
  return nullptr;
}

void StopEventLoop() {
  if (runLoop) {
    shouldStopRunLoop = true;
    CFRunLoopWakeUp(runLoop);
    pthread_join(runLoopThread, nullptr);
    shouldStopRunLoop = false;
  }
}

// Thread-safe function callback
void CallJs(napi_env env, napi_value js_callback, void *context, void *data) {
  MouseEventData *eventData = static_cast<MouseEventData *>(data);

  napi_value undefined, event_obj, button, x, y;
  napi_get_undefined(env, &undefined);

  napi_create_object(env, &event_obj);
  napi_create_int32(env, eventData->button, &button);
  napi_create_double(env, eventData->x, &x);
  napi_create_double(env, eventData->y, &y);

  napi_set_named_property(env, event_obj, "button", button);
  napi_set_named_property(env, event_obj, "x", x);
  napi_set_named_property(env, event_obj, "y", y);

  napi_call_function(env, undefined, js_callback, 1, &event_obj, nullptr);

  delete eventData;
}

// Start listening for mouse events
napi_value StartListening(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value args[1];
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  if (argc < 1) {
    napi_throw_error(env, nullptr, "Expected callback function");
    return nullptr;
  }

  // Check if already listening
  if (eventTap != nullptr) {
    napi_throw_error(env, nullptr, "Already listening for mouse events");
    return nullptr;
  }

  // Create threadsafe function
  napi_value async_resource_name;
  napi_create_string_utf8(env, "MouseListener", NAPI_AUTO_LENGTH,
                          &async_resource_name);

  napi_create_threadsafe_function(env, args[0], nullptr, async_resource_name, 0,
                                  1, nullptr, nullptr, nullptr, CallJs, &tsfn);

  // Create event tap
  CGEventMask eventMask = CGEventMaskBit(kCGEventLeftMouseDown) |
                          CGEventMaskBit(kCGEventRightMouseDown) |
                          CGEventMaskBit(kCGEventOtherMouseDown);

  eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap,
                              kCGEventTapOptionDefault, eventMask,
                              mouseEventCallback, nullptr);

  if (!eventTap) {
    napi_release_threadsafe_function(tsfn, napi_tsfn_abort);
    tsfn = nullptr;
    napi_throw_error(env, nullptr,
                     "Failed to create event tap. Make sure the app has "
                     "accessibility permissions.");
    return nullptr;
  }

  // Create run loop source
  runLoopSource =
      CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);

  // Create and start the run loop thread
  pthread_create(&runLoopThread, nullptr, RunEventLoop, nullptr);

  napi_value result;
  napi_get_boolean(env, true, &result);
  return result;
}

// Stop listening for mouse events
napi_value StopListening(napi_env env, napi_callback_info info) {
  if (eventTap != nullptr) {
    CGEventTapEnable(eventTap, false);

    // Stop the run loop thread
    StopEventLoop();

    // Clean up resources
    if (runLoopSource) {
      CFRelease(runLoopSource);
      runLoopSource = nullptr;
    }

    if (eventTap) {
      CFRelease(eventTap);
      eventTap = nullptr;
    }
  }

  if (tsfn != nullptr) {
    napi_release_threadsafe_function(tsfn, napi_tsfn_release);
    tsfn = nullptr;
  }

  napi_value result;
  napi_get_boolean(env, true, &result);
  return result;
}

// Check if currently listening
napi_value IsListening(napi_env env, napi_callback_info info) {
  napi_value result;
  napi_get_boolean(env, eventTap != nullptr, &result);
  return result;
}

} // namespace mouse_hook
