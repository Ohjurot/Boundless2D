#include "bl2d.platform.windows.h"

// === Put implementation includes here ===
#include <bl2d.platform.windows/SystemPlatformWindows.h>


const bl2d::ModuleDescription& bl2d::modules::bl2d_platform_windows::GetDesc() const
{
    static const ModuleDescription desc{
        .packageName = "bl2d.platform.windows",
        .displayName = "Windows Platform Supports",
        .description = "Implements windows specific features",
    };
    return desc;
}

void bl2d::modules::bl2d_platform_windows::Register(IoCRegistrations& registrar)
{
    // === Put implementation registers here ===
    registrar.Register<platform::ISystemPlatform, platform::SystemPlatformWindows>();
}
