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

void bl2d::MainApplication::Init()
{
    // 1) Register modules
    bl2d::RegisterAllModules();

    // 2) Call module's load callback (.)
    OnLoad();
    // ...

    // 3) Call module's init callback (M<->M)
    // ...
    OnInit();

}

void bl2d::MainApplication::Shutdown()
{
    // 1) Call module's shutdown callback (M<->M, M->O)
    OnShutdown();
    // ...

    // 2)
    ioc.Clear();

    // 3) Call module's unload callback (.)
    // ...
    OnUnload();
}
