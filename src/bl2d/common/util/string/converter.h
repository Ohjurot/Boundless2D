#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <string_view>
#include <type_traits>

namespace bl2d::util
{
    template<typename Target>
    struct StringConverter 
    {
        std::basic_string<Target> operator()(std::basic_string_view<Target> src)
        {
            return std::basic_string<Target>(src);
        }
    };

    template<>
    struct StringConverter<char>
    {
        std::basic_string<char> operator()(std::basic_string_view<char> src)
        {
            return std::basic_string<char>(src);
        }

        std::basic_string<char> operator()(std::basic_string_view<wchar_t> src)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.to_bytes(std::wstring(src));
        }
    };

    template<>
    struct StringConverter<wchar_t>
    {
        std::basic_string<wchar_t> operator()(std::basic_string_view<char> src)
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(std::string(src));
        }

        std::basic_string<wchar_t> operator()(std::basic_string_view<wchar_t> src)
        {
            return std::basic_string<wchar_t>(src);
        }
    };
}
