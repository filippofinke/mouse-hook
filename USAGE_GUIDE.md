# Example: Using mouse-hook in another project

## Installation

```bash
npm install mouse-hook
```

## TypeScript Example

```typescript
import * as mouseHook from "mouse-hook";

console.log("Starting mouse hook...");

// Start listening for mouse events
try {
  mouseHook.startListening((event) => {
    console.log(
      `Mouse button ${event.button} clicked at (${event.x}, ${event.y})`
    );
  });

  console.log("Mouse hook started successfully!");
  console.log("Currently listening:", mouseHook.isListening());

  // Stop after 10 seconds (for demo)
  setTimeout(() => {
    mouseHook.stopListening();
    console.log("Mouse hook stopped");
    process.exit(0);
  }, 10000);
} catch (error) {
  console.error("Failed to start mouse hook:", error.message);
  console.log(
    "Make sure to grant accessibility permissions to your terminal/app"
  );
}
```

## JavaScript Example

```javascript
const mouseHook = require("mouse-hook");

console.log("Starting mouse hook...");

try {
  mouseHook.startListening((event) => {
    console.log(
      `Mouse button ${event.button} clicked at (${event.x}, ${event.y})`
    );
  });

  console.log("Mouse hook started successfully!");
} catch (error) {
  console.error("Failed to start mouse hook:", error.message);
}
```

## Project Setup

1. Create a new directory for your project:

```bash
mkdir my-mouse-app
cd my-mouse-app
npm init -y
```

2. Install the mouse-hook package:

```bash
npm install mouse-hook
# Also install TypeScript if using TypeScript
npm install -D typescript @types/node ts-node
```

3. Create your main file (app.ts or app.js) with the code above

4. Run your project:

```bash
# For TypeScript
npx ts-node app.ts

# For JavaScript
node app.js
```

## Important Requirements

- **macOS only**: Your package currently only works on macOS
- **Accessibility permissions**: The app using your package needs accessibility permissions
- **Node.js compatibility**: Works with Node.js >= 12

## Troubleshooting

If users get permission errors, they need to:

1. Go to System Preferences → Security & Privacy → Privacy → Accessibility
2. Add their terminal app or the app using your package to the list
3. Make sure it's checked/enabled
