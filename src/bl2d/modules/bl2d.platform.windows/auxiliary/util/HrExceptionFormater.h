#pragma once

#include <bl2d/common/boot/os.h>
#include <bl2d/common/util/Exception.h>

#define BL2D_BUILD_WINDOWS_EXCEPTION_RAW(name, hr) \
    BL2D_BUILD_EXCEPTION_RAW(name).Detail<::bl2d::platform::windows::HrExceptionFormater>(hr)
#define BL2D_BUILD_WINDOWS_EXCEPTION(name, hr) \
    BL2D_BUILD_WINDOWS_EXCEPTION_RAW(name, hr).NewLine()

namespace bl2d::platform::windows
{
    struct HrExceptionFormater
    {
        void operator()(util::ExceptionBuilder& builder, HRESULT hr)
        {
            std::string hrMsg = "unknown";

            char* hrStr = nullptr;
            FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                nullptr,
                hr,
                0,
                (char*)&hrStr,
                0,
                nullptr
            );
            if (hrStr)
            {
                hrMsg = hrStr;
                LocalFree(hrStr);
            }

            builder.Format("HRESULT 0x{:08X} - {}", (uint32_t)hr, hrMsg);
        }
    };
}
