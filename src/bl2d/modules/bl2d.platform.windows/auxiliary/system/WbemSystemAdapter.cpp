#include "WbemSystemAdapter.h"

bl2d::platform::windows::WbemSystemAdapter::WbemSystemAdapter()
{
    HRESULT hr;
    
    hr = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_locator));
    if (FAILED(hr))
    {
        throw BL2D_BUILD_WINDOWS_EXCEPTION("CoCreateInstance", hr)
            .Text("CLSID: CLSID_WbemLocator")
            .Build();
    }
}

bl2d::platform::windows::WbemSystemAdapter::~WbemSystemAdapter()
{
    m_services.clear();
    m_locator.Release();
}

std::wstring bl2d::platform::windows::WbemSystemAdapter::Query(std::wstring_view resource, std::wstring_view cls, std::wstring_view value)
{
    HRESULT hr;

    auto& ptr = m_services[resource.data()];
    if (!ptr)
    {
        hr = m_locator->ConnectServer(_bstr_t(resource.data()), NULL, NULL, 0, NULL, 0, 0, &ptr);
        if (FAILED(hr))
        {
            throw BL2D_BUILD_WINDOWS_EXCEPTION("IWbemLocator->ConnectServer", hr)
                .Format(L"strNetworkResource: {}", resource)
                .Build();
        }

        hr = CoSetProxyBlanket(ptr, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_DEFAULT);
        if (FAILED(hr))
        {
            throw BL2D_BUILD_WINDOWS_EXCEPTION("CoSetProxyBlanket", hr)
                .Text("pProxy: IWbemServices")
                .Build();
        }
    }

    std::wstringstream wss;
    wss << L"SELECT * FROM " << cls;

    ComPointer<IEnumWbemClassObject> wbemEnum;
    hr = ptr->ExecQuery(_bstr_t(L"WQL"), _bstr_t(wss.str().c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &wbemEnum);
    if (FAILED(hr))
    {
        throw BL2D_BUILD_WINDOWS_EXCEPTION("IWbemServices->ExecQuery", hr)
            .Format(L"class: {}", cls)
            .Build();
    }

    ULONG rv;
    ComPointer<IWbemClassObject> wbemClass;
    hr = wbemEnum->Next(WBEM_INFINITE, 1, &wbemClass, &rv);
    if (FAILED(hr) || rv == 0)
    {
        throw BL2D_BUILD_WINDOWS_EXCEPTION("IEnumWbemClassObject->Next", hr)
            .Format(L"class: {}", cls)
            .Format(L"returnValue: {}", rv)
            .Build();
    }

    VARIANT target{ .vt = VT_NULL };
    hr = wbemClass->Get(value.data(), 0, &target, 0, 0);
    if (FAILED(hr))
    {
        throw BL2D_BUILD_WINDOWS_EXCEPTION("IEnumWbemClassObject->Get", hr)
            .Format(L"class: {}", cls)
            .Format(L"value: {}", value)
            .Build();
    }

    std::wstring targetValue;
    if (target.vt != VT_BSTR)
    {
        throw BL2D_BUILD_EXCEPTION("target.vt != VT_BSTR")
            .Text("Invalid type of wbem value. Only BSTR is allowed!")
            .Build();
    }
    targetValue = target.bstrVal;

    return targetValue;
}
