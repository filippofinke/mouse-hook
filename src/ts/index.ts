import * as os from "os";
import * as path from "path";

// Only support macOS for now
if (os.platform() !== "darwin") {
  throw new Error("The mouse-hook module only supports macOS at the moment");
}

// Load the native module
const nativeBinding = (() => {
  const possiblePaths = [
    // Development paths (when running from source)
    path.resolve(__dirname, "../../mouse-hook/build/Release/mouse_hook.node"),
    path.resolve(__dirname, "../../mouse-hook/build/Debug/mouse_hook.node"),
  ];

  for (const modulePath of possiblePaths) {
    try {
      return require(modulePath);
    } catch (err) {}
  }

  throw new Error(
    "Could not load native module mouse_hook.node. " +
      "Make sure the module is properly compiled. " +
      "Run 'npm install' or 'node-gyp rebuild' to build the native module. " +
      `Searched paths: ${possiblePaths.join(", ")}`
  );
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
