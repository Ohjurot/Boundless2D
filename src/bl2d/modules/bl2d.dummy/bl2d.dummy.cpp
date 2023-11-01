#include "bl2d.dummy.h"

// === Put implementation includes here ===
#include <bl2d.dummy/Dummy.h>


const bl2d::ModuleDescription& bl2d::modules::bl2d_dummy::GetDesc() const
{
    static const ModuleDescription desc{
        .packageName = "bl2d.dummy",
        .displayName = "Dummy",
        .description = "A simple hello world module",
    };
    return desc;
}

void bl2d::modules::bl2d_dummy::Register(IoCRegistrations& registrar)
{
    // === Put implementation registers here ===

    registrar.Register<bl2d::dummy::IDummy, bl2d::dummy::Dummy>();
}
