import * as os from "os";

// Only support macOS for now
if (os.platform() !== "darwin") {
  throw new Error("The mouse-hook module only supports macOS at the moment");
}

// Load the native module
const nativeBinding = (() => {
  try {
    return require("../../build/Release/mouse_hook.node");
  } catch (err) {
    return require("../../build/Debug/mouse_hook.node");
  }
})();

/**
 * Represents a mouse event with position and button information
 */
export interface MouseEvent {
  /** Mouse button (0 = left, 1 = right, 2 = other) */
  button: number;
  /** X coordinate of mouse position */
  x: number;
  /** Y coordinate of mouse position */
  y: number;
}

/**
 * Callback function for mouse events
 */
export type MouseEventCallback = (event: MouseEvent) => void;

/**
 * Start listening for mouse events
 * @param callback - Function to call on mouse events
 * @returns Success status
 * @throws Error if already listening or if permissions are missing
 */
export function startListening(callback: MouseEventCallback): boolean {
  if (typeof callback !== "function") {
    throw new TypeError("Callback must be a function");
  }
  return nativeBinding.startListening(callback);
}

/**
 * Stop listening for mouse events
 * @returns Success status
 */
export function stopListening(): boolean {
  return nativeBinding.stopListening();
}

/**
 * Check if currently listening for mouse events
 * @returns Listening status
 */
export function isListening(): boolean {
  return nativeBinding.isListening();
}
