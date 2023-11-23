#include "SystemPlatformWindows.h"

bl2d::platform::SystemPlatformWindows::SystemPlatformWindows(IoCStack& ioc)
{
    m_platformInfo.kind = PlatformKind::Windows;
    m_platformInfo.name = "Windows ??";
    m_platformInfo.version = "??";
}

void bl2d::platform::SystemPlatformWindows::Init()
{
    CoInitialize(nullptr);
    ConnectToWbem();

    QueryWMIInformations();
}

void bl2d::platform::SystemPlatformWindows::Shutdown()
{
    DisconnectFromWbem();
    CoUninitialize();
}

const bl2d::platform::PlatformInfo& bl2d::platform::SystemPlatformWindows::GetInfo() const
{
    return m_platformInfo;
}

void bl2d::platform::SystemPlatformWindows::ConnectToWbem()
{
    CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_wbemLocator));

    m_wbemLocator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &m_wbemService);
    CoSetProxyBlanket(m_wbemService, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_DEFAULT);
}

void bl2d::platform::SystemPlatformWindows::DisconnectFromWbem()
{
    m_wbemService.Release();
    m_wbemLocator.Release();
}

bool bl2d::platform::SystemPlatformWindows::QueryWbem(std::wstring_view className, std::wstring_view valueName, VARIANT& value)
{
    std::wstringstream wss;
    wss << L"SELECT * FROM " << className;

    ComPointer<IEnumWbemClassObject> wbemEnum;
    m_wbemService->ExecQuery(_bstr_t(L"WQL"), _bstr_t(wss.str().c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &wbemEnum);
    
    ULONG rv;
    ComPointer<IWbemClassObject> wbemClass;
    wbemEnum->Next(WBEM_INFINITE, 1, &wbemClass, &rv);

    wbemClass->Get(valueName.data(), 0, &value, 0, 0);

    return true;
}

void bl2d::platform::SystemPlatformWindows::QueryWMIInformations()
{
    VARIANT osName, osVersion;
    if (QueryWbem(L"Win32_OperatingSystem", L"Caption", osName))
    {
        m_winName = util::StringConverter<char>()(osName.bstrVal);
        m_platformInfo.name = m_winName.c_str();
    }
    if (QueryWbem(L"Win32_OperatingSystem", L"Version", osVersion))
    {
        m_winVersion = util::StringConverter<char>()(osVersion.bstrVal);
        m_platformInfo.version = m_winVersion.c_str();
    }
}
