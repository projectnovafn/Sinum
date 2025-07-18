// Copyright (c) 2025 Project Nova LLC

#pragma once
#include <pthread.h>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <jni.h>
#include <stdint.h>
#include <unistd.h>
#include <cstddef>
#include <cstdint>
#include "Log.h"
#include "Util.h"

namespace Library
{
    void* FindByName(const char* library_name)
    {
        FILE* fp = fopen("/proc/self/maps", "rt");
        if (fp != NULL)
        {
            char line[512], mod_name[64];
            void* base;
            while (fgets(line, sizeof(line), fp))
            {
                if (std::sscanf(line, _("%llx-%*llx %*s %*ld %*s %*d %s"), &base, mod_name))
                {
                    if (std::strstr(mod_name, library_name))
                    {
                        fclose(fp);
                        return base;
                    }
                }
            }
        }

        return nullptr;
    }

    bool IsLoaded(const char* lib)
    {
        char line[512] = { 0 };
        FILE* fp = fopen(_("/proc/self/maps"), _("rt"));
        if (fp != NULL)
        {
            while (fgets(line, sizeof(line), fp))
            {
                if (strstr(line, lib))
                    return true;
            }
            fclose(fp);
        }
        return false;
    }

    void WaitFor(const char* lib)
    {
        while (!IsLoaded(lib))
        {
            sleep(1);
        }
    }
}