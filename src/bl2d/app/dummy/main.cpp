#include <spdlog/spdlog.h>

#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/ioc/IoCRegistrations.h>

#include <i.bl2d.dummy/IDummy.h>
#include <bl2d.dummy/Dummy.h>

int main()
{
    bl2d::IoCRegistrations::Get().Register<bl2d::dummy::IDummy, bl2d::dummy::Dummy>();

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
