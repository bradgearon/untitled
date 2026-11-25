# Windows and Android builds

From a Windows x64 checkout with Git and Python 3 installed, run `run-windows.cmd` or `build-android.cmd`. Qt 5.15.2, MinGW, and Android tools are downloaded on demand to `%LOCALAPPDATA%\UntitledTools`. Override the cache with `UNTITLED_TOOLS`, or reuse an Android SDK with `UNTITLED_ANDROID_SDK`. Accept the SDK licenses when prompted.

`run-windows.cmd -BuildOnly` skips launching. `build-android.cmd -Install` installs the development APK via ADB. Default Android ABI is arm64-v8a. Build paths are printed upon success. The new standalone target combines the original source and resources without changing the original qmake library targets. It uses the Qt 5.15 Android package template in place of the old Gradle library template. This is a legacy development APK (target SDK 29), not a current Play Store build. End-to-end Windows/device builds have not been tested.
