#include "dmz.mod.h"

// === Put implementation includes here ===


const bl2d::ModuleDescription& bl2d::modules::dmz_mod::GetDesc() const
{
    static const ModuleDescription desc{
        .packageName = "dmz.mod",
        .displayName = "dmz.mod",
        .description = "",
    };
    return desc;
}

void bl2d::modules::dmz_mod::Register(IoCRegistrations& registrar)
{
    // === Put implementation registers here ===

}
