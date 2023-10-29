#pragma once

#include <functional>

namespace bl2d
{
    struct IoCRegistration
    {
        using CTor = std::function<void(void*)>;
        using DTor = std::function<void(void*)>;

        size_t objectSize;
        CTor cTor;
        DTor dTor;
    };
}
