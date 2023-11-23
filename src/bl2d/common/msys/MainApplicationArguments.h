#pragma once

#include <bl2d/common/util/string/StringConverter.h>

#include <string>
#include <vector>
#include <type_traits>
#include <unordered_map>

namespace bl2d
{
    class IMainApplicationArguments
    {
        public:
            virtual ~IMainApplicationArguments() = default;

            virtual size_t GetPositionalCount() const = 0;
            virtual std::vector<std::string> GetNamedKeys() const = 0;
            virtual std::vector<std::wstring> GetNamedWKeys() const = 0;

            virtual std::string String(size_t pos) const = 0;
            virtual std::string String(const std::string& str) const = 0;

            virtual std::wstring WString(size_t pos) const = 0;
            virtual std::wstring WString(const std::wstring& str) const = 0;
    };

    template<typename T, typename = std::enable_if_t<std::is_same_v<T, char> || std::is_same_v<T, wchar_t>>>
    class MainApplicationArguments : public IMainApplicationArguments
    {
        public:
            MainApplicationArguments(int argc, T** argv)
            {
                // name.exe pos1 pos2 -NMTrue pos3 -NM=value
                for (int i = 0; i < argc; i++)
                {
                    if (argv[i][0] == '-')
                    {
                        // Named
                        std::basic_string<T> arg = &argv[i][1];
                        auto eqPos = arg.find_first_of('=');
                        if (eqPos == std::basic_string<T>::npos)
                        {
                            // Named-True
                            auto& argx = m_namedArguments[arg];
                            argx = std::basic_string<T>();
                            argx.resize(1, '1');
                            *argx.data() = '1';
                        }
                        else
                        {
                            // Name-Value
                            std::basic_string<T> arg_name = arg.substr(0, eqPos);
                            std::basic_string<T> arg_value = arg.substr(eqPos + 1);
                            m_namedArguments[arg_name] = std::move(arg_value);
                        }
                    }
                    else
                    {
                        // Positional
                        m_positionalArguments.push_back(argv[i]);
                    }
                }
            }

            size_t GetPositionalCount() const override
            {
                return m_positionalArguments.size();
            }
            std::vector<std::string> GetNamedKeys() const override
            {
                std::vector<std::string> keys;
                for (auto it = m_namedArguments.begin(); it != m_namedArguments.end(); ++it)
                {
                    keys.push_back(util::StringConverter<char>()(it->first));
                }
                return keys;
            }
            std::vector<std::wstring> GetNamedWKeys() const override
            {
                std::vector<std::wstring> keys;
                for (auto it = m_namedArguments.begin(); it != m_namedArguments.end(); ++it)
                {
                    keys.push_back(util::StringConverter<wchar_t>()(it->first));
                }
                return keys;
            }

            std::string String(size_t pos) const override
            { 
                return util::StringConverter<char>()(m_positionalArguments[pos]);
            };
            std::string String(const std::string& str) const override
            {
                auto it = m_namedArguments.find(util::StringConverter<T>()(str));
                return util::StringConverter<char>()(it->second);
            };

            std::wstring WString(size_t pos) const override
            {
                return util::StringConverter<wchar_t>()(m_positionalArguments[pos]);
            };

            std::wstring WString(const std::wstring& str) const override
            {
                auto it = m_namedArguments.find(util::StringConverter<T>()(str));
                return util::StringConverter<wchar_t>()(it->second);
            };

        private:
            std::vector<std::basic_string<T>> m_positionalArguments;
            std::unordered_map<std::basic_string<T>, std::basic_string<T>> m_namedArguments;
    
    };
}
