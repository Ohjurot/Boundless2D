#pragma once

#include <i.bl2d.dummy/IDummy.h>

namespace bl2d::dummy
{
    class Dummy : public IDummy
    {
        public:
            void SayHello() override;

    };
}
