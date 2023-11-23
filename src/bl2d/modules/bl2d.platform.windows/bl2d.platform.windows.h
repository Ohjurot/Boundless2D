#pragma once

#include <bl2d/common/msys/IModule.h>

namespace bl2d::modules
{
    class bl2d_platform_windows : public IModule
    {
        public:
            const ModuleDescription& GetDesc() const override;
            void Register(IoCRegistrations& registrar) override;
    };
}
