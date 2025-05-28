import * as mouseHook from "../src/ts";

console.log("Mouse Hook Example");
console.log("Press Ctrl+C to exit");

// Start listening for mouse events
try {
  mouseHook.startListening((event) => {
    console.log(
      `Button ${event.button} clicked at position (${event.x}, ${event.y})`
    );

    // Map button numbers to names for readability
    const buttonNames = ["left", "right", "middle"];
    const buttonName = buttonNames[event.button] || "unknown";

    console.log(
      `${buttonName} button clicked at coordinates: (${Math.round(
        event.x
      )}, ${Math.round(event.y)})`
    );
  });

  console.log("Successfully started mouse hook");
  console.log(`Currently listening: ${mouseHook.isListening()}`);
} catch (error) {
  console.error("Failed to start mouse hook:", error);
  process.exit(1);
}

// Handle graceful shutdown
process.on("SIGINT", () => {
  console.log("\nStopping mouse hook...");
  mouseHook.stopListening();
  console.log("Mouse hook stopped");
  process.exit(0);
});
