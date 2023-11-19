#include <bl2d/common/msys/ModuleManager.h>

#include <bl2d.dummy/bl2d.dummy.h>


void bl2d::RegisterAllModules()
{
    ::bl2d::ModuleManager::Get().Register<bl2d::modules::bl2d_dummy>();

}
