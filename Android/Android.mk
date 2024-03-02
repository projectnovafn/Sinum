LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

LOCAL_MODULE := dobby
LOCAL_SRC_FILES := Dobby/arm64-v8a/libdobby.a
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