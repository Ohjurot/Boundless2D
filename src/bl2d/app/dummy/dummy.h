#pragma once

#include <spdlog/spdlog.h>

#include <i.bl2d.platform/ISystemPlatform.h>

#include <bl2d/common/msys/MainApplication.h>
#include <bl2d/common/util/Exception.h>

class dummy : public bl2d::MainApplication
{
    public:
        int Run(const IMainApplicationArguments& args) override;
};
