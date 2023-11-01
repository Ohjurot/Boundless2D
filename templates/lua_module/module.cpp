#include "<<name_dt>>.h"

// === Put implementation includes here ===


const bl2d::ModuleDescription& bl2d::modules::<<name_us>>::GetDesc() const
{
    static const ModuleDescription desc{
        .packageName = "<<name_dt>>",
        .displayName = "<<name_dt>>",
        .description = "",
    };
    return desc;
}

void bl2d::modules::<<name_us>>::Register(IoCRegistrations& registrar)
{
    // === Put implementation registers here ===

}
