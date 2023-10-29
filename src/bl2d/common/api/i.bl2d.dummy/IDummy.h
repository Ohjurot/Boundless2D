#pragma once

namespace bl2d::dummy
{
    class IDummy
    {
        public:
            virtual ~IDummy() = default;

            virtual void SayHello() = 0;
    };
}
