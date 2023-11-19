#include "DummyApp.h"

int DummyApp::Run(const IMainApplicationArguments& args)
{
    // Register module and debug print
    for (size_t i = 0; i < bl2d::ModuleManager::Get().GetModuleCount(); i++)
        spdlog::info("Module: {} ({})",
            bl2d::ModuleManager::Get().GetModuleDetail(i)->displayName,
            bl2d::ModuleManager::Get().GetModuleDetail(i)->packageName
        );

    // Arguments
    for (size_t i = 0; i < args.GetPositionalCount(); i++)
    {
        spdlog::info("Arg {}: {}", i, args.String(i));
    }
    for (auto key : args.GetNamedWKeys())
    {
        spdlog::info(L"Arg {}: {}", key, args.WString(key));
    }

    // Module demo
    auto* dmy = &ioc.Get<bl2d::dummy::IDummy>();
    dmy->SayHello();

    return 0;
}
