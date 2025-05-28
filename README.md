<h1 align="center">Welcome to mouse-hook</h1>

> A native Node.js module for hooking into mouse events on macOS

## Features

- [x] Native mouse event hooking on macOS
- [x] TypeScript support with type definitions
- [x] Simple callback-based API
- [x] Real-time mouse click detection
- [x] Position tracking (x, y coordinates)
- [x] Button identification (left, right, other)

## Install

```bash
npm install mouse-hook
```

**Requirements:**

- macOS (Currently only supports macOS)
- Node.js >= 12
- Accessibility permissions must be granted to the application using this module

## Usage

### TypeScript

```typescript
import * as mouseHook from "mouse-hook";

// Start listening for mouse events
mouseHook.startListening((event) => {
  console.log(
    `Button ${event.button} clicked at position (${event.x}, ${event.y})`
  );
});

// Check if currently listening
console.log(`Currently listening: ${mouseHook.isListening()}`);

// Stop listening when done
// mouseHook.stopListening();
```

### JavaScript

```javascript
const mouseHook = require("mouse-hook");

// Start listening for mouse events
mouseHook.startListening((event) => {
  console.log(
    `Button ${event.button} clicked at position (${event.x}, ${event.y})`
  );
});
```

### API Reference

#### Types

```typescript
interface MouseEvent {
  button: number; // 0 = left, 1 = right, 2 = other
  x: number; // x-coordinate
  y: number; // y-coordinate
}

type MouseEventCallback = (event: MouseEvent) => void;
```

#### Methods

- `startListening(callback: MouseEventCallback): boolean` - Start listening for mouse events
- `stopListening(): boolean` - Stop listening for mouse events
- `isListening(): boolean` - Check if currently listening for mouse events

### Running Examples

```bash
# Run the basic example
npm run example

# Run the advanced example (with TypeScript)
npx ts-node examples/advanced.ts
```

## Development

```bash
# Install dependencies
npm install

# Build the native module and TypeScript
npm run rebuild

# Clean build files
npm run clean
```

**Note:** This module requires accessibility permissions to access mouse events. When your application attempts to use mouse-hook for the first time, macOS will prompt the user for these permissions.

## Author

👤 **Filippo Finke**

- Website: [https://filippofinke.ch](https://filippofinke.ch)
- Twitter: [@filippofinke](https://twitter.com/filippofinke)
- Github: [@filippofinke](https://github.com/filippofinke)
- LinkedIn: [@filippofinke](https://linkedin.com/in/filippofinke)
