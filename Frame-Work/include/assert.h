#pragma once

namespace cs
{
    void assert_failed(const char*, const char*, int);
}

#define CS_ASSERT(x) do \
{\
    if (!(x))\
    {\
        cs::assert_failed(#x, __FILE__, __LINE__)\
    };\
}\
while(false)