#include "dummy.h"

int dummy::Run(const IMainApplicationArguments& args)
{
    spdlog::default_logger()->set_pattern("[%^%Y-%m-%d %H:%M:%S.%e%$] [%t] [%l] %v");

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
    spdlog::info("The computer has {} CPU-Cores", ioc.Get<bl2d::platform::IThreadFactory>().GetSystemThreadCount());

    // Let async run
    auto& threadFactory = ioc.Get<bl2d::platform::IThreadFactory>();
    auto thread = threadFactory.CreateSuspendedThread(std::bind(&dummy::AsyncOps, this, std::placeholders::_1, std::placeholders::_2));
    thread->Start();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    thread->Stop();
    thread->Wait(2000);

    return 0;
}

bl2d::platform::ThreadReturnCode dummy::AsyncOps(bl2d::platform::IThread& thread, const bool& shouldStop)
{
    size_t c = 0;
    while (!shouldStop)
    {
        spdlog::info("I'm async {}!", c++);

        if (c == 100)
        {
            throw BL2D_BUILD_EXCEPTION("Idiot!").Build();
        }
    }
    return 0;
}
