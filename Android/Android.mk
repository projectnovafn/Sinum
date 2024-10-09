LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

ifeq ($(TARGET_ABI),armeabi-v7a)
    LOCAL_SRC_FILES := Dobby/armeabi-v7a/libdobby.a
else ifeq ($(TARGET_ABI),arm64-v8a)
    LOCAL_SRC_FILES := Dobby/arm64-v8a/libdobby.a
else ifeq ($(TARGET_ABI),x86)
    LOCAL_SRC_FILES := Dobby/x86/libdobby.a
else ifeq ($(TARGET_ABI),x86_64)
    LOCAL_SRC_FILES := Dobby/x86_64/libdobby.a
else
    LOCAL_SRC_FILES := Dobby/arm64-v8a/libdobby.a
endif

LOCAL_MODULE := dobby
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := sinum

LOCAL_CFLAGS := -Wno-error=format-security -fpermissive
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -g --std=c++2a

LOCAL_STATIC_LIBRARIES := dobby

LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)

LOCAL_SRC_FILES := Main.cpp

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
