#pragma once

#include <bl2d/common/ioc/IoCRegistration.h>
#include <bl2d/common/ioc/IoCRegistrations.h>

#include <list>
#include <typeindex>
#include <string_view>
#include <unordered_map>

namespace bl2d
{
    class IoCStack
    {
        private:
            struct StackElement
            {
                IoCRegistration descriptor;
                void* instance = nullptr;
            };

        public:
            IoCStack() = default;
            IoCStack(const IoCStack&) = delete;
            IoCStack(IoCStack&&) noexcept = default;
            ~IoCStack();

            IoCStack& operator=(const IoCStack&) = delete;
            IoCStack& operator=(IoCStack&&) noexcept = default;

            template<typename T>
            T& Get(std::string_view name = "")
            {
                auto* ptr = (T*)GetPtr(typeid(T), name);
                // TODO: Check
                return *ptr;
            }

            void* GetPtr(std::type_index type, std::string_view name = "");

            void Clear();

            inline void SetParent(IoCStack& stack) { m_parent = &stack; }
            inline IoCStack& GetParent() { return *m_parent; }

        private:
            StackElement* Push(std::type_index type, std::string_view name = "");

        private:
            IoCStack* m_parent = nullptr;
            std::list<StackElement> m_stack;
            std::unordered_map<std::type_index, std::unordered_map<std::string, StackElement*>> m_apiToStack;
    };
}
