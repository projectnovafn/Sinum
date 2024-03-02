// Copyright (c) 2024 Project Nova LLC

#ifndef LOGGER_H
#define LOGGER_H
#include <android/log.h>

enum daLogType {
    daDEBUG = 3,
    daERROR = 6,
    daINFO  = 4,
    daWARN  = 5
};

#define TAG _("sinum")

#define LOGD(...) ((void)__android_log_print(daDEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(daERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(daINFO,  TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(daWARN,  TAG, __VA_ARGS__))

#endif //LOGGER_H