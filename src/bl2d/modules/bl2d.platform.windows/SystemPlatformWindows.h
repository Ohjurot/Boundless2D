#pragma once

#include <i.bl2d.platform/ISystemPlatform.h>

#include <bl2d/common/boot/os.h>
#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/util/string/StringConverter.h>

#include <bl2d.platform.windows/auxiliary/system/WbemSystemAdapter.h>

#include <string>
#include <sstream>
#include <memory>
#include <string_view>

namespace bl2d::platform
{
    class SystemPlatformWindows : public ISystemPlatform
    {
        public:
            SystemPlatformWindows(IoCStack& ioc);

            // === Interface
            void Init() override;
            void Shutdown() override;
            const PlatformInfo& GetInfo() const override;

        private:
            void QueryWMIInformations();

        private:
            PlatformInfo m_platformInfo;
            std::string m_winName;
            std::string m_winVersion;

            std::unique_ptr<windows::WbemSystemAdapter> m_wbem;
    };
}
