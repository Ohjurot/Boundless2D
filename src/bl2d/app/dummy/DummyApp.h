#pragma once

#include <spdlog/spdlog.h>

#include <i.bl2d.dummy/IDummy.h>
#include <bl2d/common/msys/MainApplication.h>

class DummyApp : public bl2d::MainApplication
{
    public:
        int Run(const IMainApplicationArguments& args) override;
};
