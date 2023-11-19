#include "<<app_name>>.h"

int <<app_name>>::Run(const IMainApplicationArguments& args)
{
    spdlog::info("\"Hello World!\" From the \"{}\" app!", "<<app_name>>");

    return 0;
}
