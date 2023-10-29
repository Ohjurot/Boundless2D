#pragma once

#include <functional>

namespace bl2d
{
    class IoCStack;

    struct IoCRegistration
    {
        using CTor = std::function<void(void*, IoCStack&)>;
        using DTor = std::function<void(void*)>;

        size_t objectSize;
        CTor cTor;
        DTor dTor;
    };
}
