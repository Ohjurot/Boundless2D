#pragma once

#include <bl2d/common/ioc/IoCRegistration.h>

#include <string>
#include <typeindex>
#include <string_view>
#include <unordered_map>

namespace bl2d
{
    class IoCRegistrations
    {
        public:
            template<typename T>
            const IoCRegistration* Lookup() const
            {
                return Lookup<T>("");
            }

            template<typename T>
            const IoCRegistration* Lookup(std::string_view name) const
            {
                const IoCRegistration* registration = nullptr;
                auto itType = m_registrations.find(typeid(T));
                if (itType != m_registrations.end())
                {
                    const auto& map2 = itType->second;
                    auto itName = map2.find(std::string(name));
                    if (itName != map2.end())
                    {
                        registration = &itName->second;
                    }
                }

                return registration;
            }

            template<typename API, typename Instance>
            void Register(std::string_view name = "")
            {
                auto& registration = Set<API, Instance>(name);
                registration.cTor = [](void* o) { new((Instance*)o)Instance(); };
                registration.dTor = [](void* o) { ((Instance*)o)->~Instance(); };
            }

        private:
            template<typename API, typename Instance>
            IoCRegistration& Set(std::string_view name)
            {
                auto& bin = m_registrations[typeid(API)];
                auto& registration = bin[std::string(name)];
                registration.objectSize = sizeof(Instance);
                return registration;
            }

        private:
            std::unordered_map<std::type_index, std::unordered_map<std::string, IoCRegistration>> m_registrations;
    };
}
