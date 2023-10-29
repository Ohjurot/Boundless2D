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
            static IoCRegistrations& Get();

            template<typename T>
            const IoCRegistration* Lookup(std::string_view name = "") const
            {
                return Lookup(typeid(T), name);
            }

            const IoCRegistration* Lookup(std::type_index type, std::string_view name = "") const;

            template<typename API, typename Instance>
            void Register(std::string_view name = "")
            {
                auto& registration = Set<API, Instance>(name);
                registration.cTor = [](void* o, IoCStack& stack) { new((Instance*)o)Instance(stack); };
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

            IoCRegistrations() = default;
            IoCRegistrations(const IoCRegistrations&) = delete;
            IoCRegistrations(IoCRegistrations&&) noexcept = delete;

        private:
            std::unordered_map<std::type_index, std::unordered_map<std::string, IoCRegistration>> m_registrations;
    };
}
