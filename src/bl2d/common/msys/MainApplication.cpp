#include "MainApplication.h"

bl2d::MainApplication::MainApplication()
{
    Exception ex;
    if (!util::ExceptionSafeCall(ex, [&](){ Init(); }))
    {
        OnException(ex);
    }
}

bl2d::MainApplication::~MainApplication()
{
    if (m_isInitialized)
    {
        Exception ex;
        if (!util::ExceptionSafeCall(ex, [&]() { Shutdown(); }))
        {
            OnException(ex);
        }
    }
}

int bl2d::MainApplication::RunSafe(const IMainApplicationArguments& args)
{
    int rc = -1;
    Exception ex;
    if (!util::ExceptionSafeCall(ex, [&]() { rc = Run(args); }))
    {
        OnException(ex);
    }
    return rc;
}

int bl2d::MainApplication::Run(const IMainApplicationArguments& args)
{
    return -1;
}

void bl2d::MainApplication::OnInit()
{
    ioc.Get<platform::ISystemPlatform>().Init();
}

void bl2d::MainApplication::OnShutdown()
{
    ioc.Get<platform::ISystemPlatform>().Shutdown();
}

void bl2d::MainApplication::OnException(const Exception& ex)
{
    ex.LogMessage(*spdlog::default_logger());

    // TODO: Alert the user
}

void bl2d::MainApplication::Init()
{
    // 1) Register modules
    bl2d::RegisterAllModules();

    // 2) Call module's load callback (.)
    OnLoad();
    for (size_t i = 0; i < ModuleManager::Get().GetModuleCount(); i++)
    {
        ModuleManager::Get().GetModulePtr(i)->OnLoad();
    }

    // 3) Call module's init callback (M<->M)
    OnInit();
    for (size_t i = 0; i < ModuleManager::Get().GetModuleCount(); i++)
    {
        ModuleManager::Get().GetModulePtr(i)->OnInit();
    }

    m_isInitialized = true;
}

void bl2d::MainApplication::Shutdown()
{
    // 1) Call module's shutdown callback (M<->M, M->O)
    for (size_t i = 0; i < ModuleManager::Get().GetModuleCount(); i++)
    {
        ModuleManager::Get().GetModulePtr(i)->OnShutdown();
    }
    OnShutdown();

    // 2)
    ioc.Clear();

    // 3) Call module's unload callback (.)
    for (size_t i = 0; i < ModuleManager::Get().GetModuleCount(); i++)
    {
        ModuleManager::Get().GetModulePtr(i)->OnUnload();
    }
    OnUnload();

    m_isInitialized = false;
}
