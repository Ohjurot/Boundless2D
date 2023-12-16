#pragma once

#include <bl2d/common/boot/os.h>
#include <bl2d.platform.windows/auxiliary/util/HrExceptionFormater.h>

#include <string>
#include <string_view>
#include <unordered_map>

namespace bl2d::platform::windows
{
    class WbemSystemAdapter
    {
        public:
            WbemSystemAdapter();
            ~WbemSystemAdapter();

            std::wstring Query(std::wstring_view resource, std::wstring_view cls, std::wstring_view value);

        private:
            ComPointer<IWbemLocator> m_locator;
            std::unordered_map<std::wstring, ComPointer<IWbemServices>> m_services;
    };
}
