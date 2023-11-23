#pragma once

#include <bl2d/common/util/string/StringConverter.h>

#include <fmt/format.h>
#include <fmt/xchar.h>
#include <spdlog/spdlog.h>

#include <string>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <string_view>

#define BL2D_BUILD_EXCEPTION(what) ::bl2d::util::ExceptionBuilder().What(what).Where(__FUNCTION__, __LINE__)

namespace bl2d::util
{
    class Exception : public std::runtime_error
    {
        public:
            using std::runtime_error::runtime_error;

            void LogMessage(spdlog::logger& logger, spdlog::level::level_enum level = spdlog::level::critical) const;
    };

    /*!
     * @brief Helper class for exception building
    */
    class ExceptionBuilder
    {
        public:
            ExceptionBuilder() = default;
            ExceptionBuilder(const ExceptionBuilder&) = delete;
            inline ExceptionBuilder(char seperator) : MSG_SEPERATOR(seperator) {}

            ExceptionBuilder& operator=(const ExceptionBuilder&) = delete;

            inline ExceptionBuilder& Text(std::string_view msg)
            {
                m_buffer << msg << MSG_SEPERATOR;
                return *this;
            }

            inline ExceptionBuilder& Text(std::wstring_view msg)
            {
                m_buffer << StringConverter<char>()(msg) << MSG_SEPERATOR;
                return *this;
            }

            template<typename... Args>
            inline ExceptionBuilder& Format(fmt::format_string<Args...> fstr, Args... args)
            {
                m_buffer << fmt::format(fstr, std::forward<Args>(args)...) << MSG_SEPERATOR;
                return *this;
            }

            template<typename... Args>
            inline ExceptionBuilder& Format(fmt::wformat_string<Args...> fstr, Args... args)
            {
                m_buffer << StringConverter<char>()(fmt::format(fstr, std::forward<Args>(args)...)) << MSG_SEPERATOR;
                return *this;
            }

            inline ExceptionBuilder& What(std::string_view msg)
            {
                return Format("Exception occurred: ", msg);
            }

            inline ExceptionBuilder& What(std::wstring_view msg)
            {
                return Format(L"Exception occurred: ", msg);
            }

            inline ExceptionBuilder& Where(const char* function, int line)
            {
                return Format("In {} (Line {})", function, line);
            }

            template<typename Formater, typename... Args>
            inline ExceptionBuilder& Detail(Args... args)
            {
                Formater()(*this, std::forward<Args>(args)...);
                return *this;
            }

            inline Exception Build() const
            {
                return Exception(m_buffer.str());
            }

        private:
            const char MSG_SEPERATOR = '\n';
            std::stringstream m_buffer;
    };

}
