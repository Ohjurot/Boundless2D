#include "MainApplication.h"

bl2d::MainApplication::MainApplication()
{
    Init();
}

bl2d::MainApplication::~MainApplication()
{
    Shutdown();
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
}
