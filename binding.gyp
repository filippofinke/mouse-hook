{
  "targets": [
    {
      "target_name": "mouse_hook",
      "sources": [
        "src/mouse_hook.cc",
        "src/macos/mouse_hook_mac.cc"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.10",
        "OTHER_LDFLAGS": [
          "-framework CoreGraphics"
        ]
      }
    }
  ]
}
