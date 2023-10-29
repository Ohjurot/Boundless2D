#pragma once

#include <bl2d/common/ioc/IoCStack.h>
#include <i.bl2d.dummy/IDummy.h>

namespace bl2d::dummy
{
    class Dummy : public IDummy
    {
        public:
            Dummy(IoCStack&) {};

            void SayHello() override;

    };
}
