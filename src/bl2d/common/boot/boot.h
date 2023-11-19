#pragma once

// === Include
#include <bl2d/common/boot/os.h>
#include <bl2d/common/msys/MainApplication.h>
#include <bl2d/common/msys/MainApplicationArguments.h>

#include <bl2d/common/boot/universal/boot.h>
#if defined(BL2D_OS_WINDOWS)
    #include <bl2d/common/boot/windows/boot.h>
#endif

// === Macro

// BL2D_BOOT_APP
#if defined(BL2D_OS_WINDOWS)
    #if defined(BL2D_WINDOWED)
        #define BL2D_BOOT_APP(APP_CLS) BL2D_BOOT_APP__WINDOWS_WWINMAIN(APP_CLS)
    #else
        #define BL2D_BOOT_APP(APP_CLS) BL2D_BOOT_APP__WINDOWS_WMAIN(APP_CLS)
    #endif
#else
    #define BL2D_BOOT_APP(APP_CLS) BL2D_BOOT_APP__UNIVERSAL(APP_CLS)
#endif


// === Code
#if defined(BL2D_IMPLEMENT_BOOT)
    
#endif
