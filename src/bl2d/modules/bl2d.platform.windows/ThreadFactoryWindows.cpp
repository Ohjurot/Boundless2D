#include "ThreadFactoryWindows.h"

size_t bl2d::platform::ThreadFactoryWindows::GetSystemThreadCount()
{
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
}

bl2d::platform::ThreadPtr bl2d::platform::ThreadFactoryWindows::CreateSuspendedThread(const ThreadFunction& function)
{
    return std::make_shared<ThreadWindows>(function);
}
