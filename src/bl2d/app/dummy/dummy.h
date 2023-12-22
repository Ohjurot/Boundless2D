#pragma once

#include <spdlog/spdlog.h>

#include <i.bl2d.platform/ISystemPlatform.h>
#include <i.bl2d.platform/IThreadFactory.h>

#include <bl2d/common/msys/MainApplication.h>
#include <bl2d/common/util/Exception.h>

#include <thread>

class dummy : public bl2d::MainApplication
{
    public:
        int Run(const IMainApplicationArguments& args) override;

        bl2d::platform::ThreadReturnCode AsyncOps(bl2d::platform::IThread& thread, const bool& shouldStop);
};
