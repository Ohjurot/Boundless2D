#include "Exception.h"

void bl2d::util::Exception::LogMessage(spdlog::logger& logger, spdlog::level::level_enum level /*= spdlog::level::critical*/) const
{
    std::string msg = what();
    while (!msg.empty())
    {
        auto pos = msg.find_first_of('\n');
        if (pos == std::string::npos)
        {
            break;
        }

        auto msgPart = msg.substr(0, pos);
        msg = msg.substr(pos + 1);
        logger.log(level, msgPart);
    }
    if (!msg.empty())
    {
        logger.log(level, msg);
    }
}
