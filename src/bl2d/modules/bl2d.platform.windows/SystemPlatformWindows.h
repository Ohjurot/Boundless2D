#pragma once

#include <bl2d/common/boot/os.h>
#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/util/string/StringConverter.h>

#include <i.bl2d.platform/ISystemPlatform.h>

#include <string>
#include <sstream>
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
            void ConnectToWbem();
            void DisconnectFromWbem();
            bool QueryWbem(std::wstring_view className, std::wstring_view valueName, VARIANT& value);

            void QueryWMIInformations();

        private:
            PlatformInfo m_platformInfo;
            std::string m_winName;
            std::string m_winVersion;

            ComPointer<IWbemLocator> m_wbemLocator;
            ComPointer<IWbemServices> m_wbemService;
    };
}
