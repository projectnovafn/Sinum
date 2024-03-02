# Sinum Android

Sinum Android redirects requests via hooking **curl_easy_setopt** and modifying the outgoing url to https://api.novafn.dev.

## Building & Usage

### Requirements

- Android NDK - Install [Android Studio](https://developer.android.com/studio) (recommended) or using [Standalone](https://developer.android.com/ndk/downloads)
- [apktool](https://apktool.org/)

### Build steps

1. Locate the NDK path and the `ndk-build` file.
2. Copy the full path to it.
2. `<ndk-build> NDK_PROJECT_PATH=./ NDK_APPLICATION_MK=Application.mk`

### Packaging steps

1. `apktool decode ./mod/fortnite.apk -o ./mod/apk`
2. Patch `./smali/com/epicgames/ue4/GameActivity.smali`
```diff
.method public onCreate(Landroid/os/Bundle;)V
    .locals 11
    
+   const-string v0, "sinum"
+   invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```
- Optional (disables minimal system requirements)
```diff
.method private processSystemInfo(Ljava/lang/String;Ljava/lang/String;)Z
    .locals 29
    
+   const/4 v0, 0x1
+   return v0

    :try_start_0 
```
2. `cp ./libs/arm64-v8a/libsinum.so ./mod/apk/lib/arm64-v8a/libsinum.so`
3. `apktool build ./mod/apk -o ./mod/unsigned.apk`