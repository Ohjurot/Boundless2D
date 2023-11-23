#include "dummy.h"

int dummy::Run(const IMainApplicationArguments& args)
{
    // Register module and debug print
    for (size_t i = 0; i < bl2d::ModuleManager::Get().GetModuleCount(); i++)
        spdlog::info("Module: {} ({})",
            bl2d::ModuleManager::Get().GetModuleDetail(i)->displayName,
            bl2d::ModuleManager::Get().GetModuleDetail(i)->packageName
        );

    // Print Arguments
    for (size_t i = 0; i < args.GetPositionalCount(); i++)
    {
        spdlog::info("Arg {}: {}", i, args.String(i));
    }
    for (auto key : args.GetNamedWKeys())
    {
        spdlog::info(L"Arg {}: {}", key, args.WString(key));
    }

    // Print platform
    const auto& platformInfo = ioc.Get<bl2d::platform::ISystemPlatform>().GetInfo();
    spdlog::info("Running on {} (Version: {})", platformInfo.name, platformInfo.version);

    // Exception
    auto ex = BL2D_BUILD_EXCEPTION("Example").Build();
    ex.LogMessage(*spdlog::default_logger());

    return 0;
}
