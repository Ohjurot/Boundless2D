#include "SystemPlatformWindows.h"

bl2d::platform::SystemPlatformWindows::SystemPlatformWindows(IoCStack& ioc)
{
    m_platformInfo.kind = PlatformKind::Windows;
    m_platformInfo.name = "Windows ??";
    m_platformInfo.version = "??";
}

void bl2d::platform::SystemPlatformWindows::Init()
{
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr))
    {
        throw BL2D_BUILD_WINDOWS_EXCEPTION("CoInitialize", hr)
            .Build();
    }

    m_wbem = std::make_unique<windows::WbemSystemAdapter>();

    QueryWMIInformations();
}

void bl2d::platform::SystemPlatformWindows::Shutdown()
{
    m_wbem.reset();
    CoUninitialize();
}

const bl2d::platform::PlatformInfo& bl2d::platform::SystemPlatformWindows::GetInfo() const
{
    return m_platformInfo;
}

void bl2d::platform::SystemPlatformWindows::QueryWMIInformations()
{
    m_winName = util::StringConverter<char>()(
        m_wbem->Query(L"ROOT\\CIMV2", L"Win32_OperatingSystem", L"Caption")
        );
    m_platformInfo.name = m_winName.c_str();

    m_winVersion = util::StringConverter<char>()(
        m_wbem->Query(L"ROOT\\CIMV2", L"Win32_OperatingSystem", L"Version")
        );
    m_platformInfo.version = m_winVersion.c_str();
}
