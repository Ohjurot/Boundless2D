#pragma once

#include <i.bl2d.platform/IThreadFactory.h>

#include <bl2d/common/boot/os.h>
#include <bl2d/common/ioc/IoCStack.h>

#include <bl2d.platform.windows/ThreadWindows.h>

namespace bl2d::platform
{
    class ThreadFactoryWindows : public IThreadFactory
    {
        public:
            ThreadFactoryWindows(IoCStack& stack) {};

            size_t GetSystemThreadCount() override;
            ThreadPtr CreateSuspendedThread(const ThreadFunction& function) override;

    };
}
