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
        if (!msgPart.empty())
        {
            logger.log(level, msgPart);
        }
    }
    if (!msg.empty())
    {
        logger.log(level, msg);
    }
}

std::string bl2d::util::Exception::Striped() const
{
    std::string msg = what();
    auto pos = msg.find_last_of('\n');
    if (pos != std::string::npos)
    {
        msg = msg.substr(0, pos);
    }

    return msg;
}
