#pragma once

#include <spdlog/spdlog.h>

#include <bl2d/common/msys/MainApplication.h>

class dummy : public ::bl2d::MainApplication
{
    public:
        int Run(const IMainApplicationArguments& args) override;
};
