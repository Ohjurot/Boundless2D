#include <bl2d/common/msys/ModuleManager.h>

#include <bl2d.platform.windows/bl2d.platform.windows.h>


void bl2d::RegisterAllModules()
{
    ::bl2d::ModuleManager::Get().Register<bl2d::modules::bl2d_platform_windows>();

}
