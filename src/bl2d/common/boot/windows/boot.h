#pragma once

// === Macro
#define BL2D_BOOT_APP__WINDOWS_WMAIN(APP_CLS) \
int wmain(int argc, wchar_t** argv) \
{ \
    APP_CLS app; \
    return ::bl2d::boot::WCHAR_MAIN(app, argc, argv); \
}

#define BL2D_BOOT_APP__WINDOWS_WWINMAIN(APP_CLS) \
INT WINAPI wWinMain(HINSTANCE _In_ hInstance, HINSTANCE _In_opt_ hPrevInstance, PWSTR _In_ pCmdLine, int _In_ nCmdShow) \
{ \
    APP_CLS app; \
    int argc = 0; \
    wchar_t** argv = (wchar_t**)CommandLineToArgvW(pCmdLine, &argc); \
    return ::bl2d::boot::WCHAR_MAIN(app, argc, argv); \
}

// === Code
#if defined(BL2D_IMPLEMENT_BOOT)

// INCLUDES

// FUNCTIONS

#endif
