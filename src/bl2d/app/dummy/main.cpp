#include <spdlog/spdlog.h>

#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/ioc/IoCRegistrations.h>
#include <bl2d/common/msys/ModuleManager.h>

#include <i.bl2d.dummy/IDummy.h>

#include <bl2d.dummy/bl2d.dummy.h>

int main()
{
    // Register module and debug print
    bl2d::RegisterAllModules();
    for (size_t i = 0; i < bl2d::ModuleManager::Get().GetModuleCount(); i++)
        spdlog::info("Module: {} ({})", 
            bl2d::ModuleManager::Get().GetModuleDetail(i)->displayName, 
            bl2d::ModuleManager::Get().GetModuleDetail(i)->packageName
        );

    // Module demo
    bl2d::IoCStack stack;
    auto* dmy = &stack.Get<bl2d::dummy::IDummy>();
    dmy->SayHello();
    stack.Clear();
}
