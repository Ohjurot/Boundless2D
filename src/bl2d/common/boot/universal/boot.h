#pragma once

// === Macro
#define BL2D_BOOT_APP__UNIVERSAL(APP_CLS) \
int main(int argc, char** argv) \
{ \
    APP_CLS app; \
    return ::bl2d::boot::CHAR_MAIN(app, argc, argv)\
}

// === Code
namespace bl2d::boot
{
    int CHAR_MAIN(::bl2d::MainApplication& app, int argc, char** argv);
    int WCHAR_MAIN(::bl2d::MainApplication& app, int argc, wchar_t** argv);
}

#if defined(BL2D_IMPLEMENT_BOOT)

namespace bl2d::boot
{
    template<typename T>
    int TCHAR_MAIN(::bl2d::MainApplication& app, int argc, T** argv)
    {
        int rc = -1;

        ::bl2d::MainApplicationArguments<T> args(argc, argv);
        if (app.IsInitialized())
        {
            rc = app.RunSafe(args);
        }

        return rc;
    }
}

int bl2d::boot::WCHAR_MAIN(::bl2d::MainApplication& app, int argc, wchar_t** argv)
{
    return ::bl2d::boot::TCHAR_MAIN<wchar_t>(app, argc, argv);
}

int bl2d::boot::CHAR_MAIN(::bl2d::MainApplication& app, int argc, char** argv)
{
    return ::bl2d::boot::TCHAR_MAIN<char>(app, argc, argv);
}

#endif
