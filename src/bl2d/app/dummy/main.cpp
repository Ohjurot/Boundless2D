#include <spdlog/spdlog.h>

#include <bl2d/common/ioc/IoCRegistrations.h>

#include <i.bl2d.dummy/IDummy.h>
#include <bl2d.dummy/Dummy.h>

int main()
{
    bl2d::IoCRegistrations rgs;
    rgs.Register<bl2d::dummy::IDummy, bl2d::dummy::Dummy>();

    const auto* info = rgs.Lookup<bl2d::dummy::IDummy>();
    auto* myDummy = (bl2d::dummy::IDummy*)malloc(info->objectSize);
    info->cTor(myDummy);

    myDummy->SayHello();

    // We will use spdlog to say hello! 
    // So that you can see that conan works :-)
    spdlog::warn("Hello World!");
}
