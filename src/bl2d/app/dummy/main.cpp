#include <spdlog/spdlog.h>

#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/ioc/IoCRegistrations.h>

#include <i.bl2d.dummy/IDummy.h>

#include <bl2d.dummy/bl2d.dummy.h>

int main()
{
    bl2d::modules::bl2d_dummy modDummy;
    modDummy.Register(bl2d::IoCRegistrations::Get());

    bl2d::IoCStack stack;

    auto* myDummy1 = &stack.Get<bl2d::dummy::IDummy>();
    auto* myDummy2 = &stack.Get<bl2d::dummy::IDummy>();
    auto* myDummy3 = &stack.Get<bl2d::dummy::IDummy>();
    myDummy1->SayHello();

    stack.Clear();

    // We will use spdlog to say hello! 
    // So that you can see that conan works :-)
    spdlog::warn("Hello World!");
}
