// Copyright (c) 2025 Project Nova LLC

#pragma once
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <jni.h>
#include "Includes/xorstr.hpp"

#define _(str) xorstr(str).crypt_get()

namespace Util
{
    bool IsPointerBad(void* p)
    {
        int fh = open((const char*)p, 0, 0);
        int e = errno;

        if (-1 == fh && e == EFAULT)
        {
            return true;
        }
        else if (fh != -1)
        {
            close(fh);
        }

        return false;
    }
}