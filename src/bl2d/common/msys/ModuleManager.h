#pragma once

#include <bl2d/common/ioc/IoCRegistrations.h>
#include <bl2d/common/msys/IModule.h>

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <type_traits>

namespace bl2d
{
    void RegisterAllModules();

    /*!
     * @brief Singleton that manges all modules
    */
    class ModuleManager
    {
        // Class
        public:
            /*!
             * @brief Registers newly created instance of a module
             * @tparam T Module type
             * @tparam ...Args Type of arguments
             * @param ...args Arguments
            */
            template<typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<IModule, T>>>
            void Register(Args... args)
            {
                Register(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
            }

            /*!
             * @brief Registers a created module
             * @param module Pointer to module instance (moved to this class)
            */
            void Register(std::unique_ptr<IModule>&& module);

            /*!
             * @brief Retrieves the details of a module by it's package name
             * @param packageName Package name of the module
             * @return Pointer to the descriptor or null
            */
            const ModuleDescription* GetModuleDetail(const std::string& packageName) const;

            /*!
             * @brief Retrieves the details of a module by it's internal index
             * @param index Index of module
             * @return Pointer to the descriptor (never null, only exception)
            */
            const ModuleDescription* GetModuleDetail(size_t index) const;

            /*!
             * @brief Counts the number of registered modules
             * @return Module count
            */
            size_t GetModuleCount() const;

        private:
            std::map<std::string, std::unique_ptr<IModule>> m_modules;

        // Singleton
        public:
            inline static ModuleManager& Get()
            {
                static ModuleManager instance;
                return instance;
            }

        private:
            ModuleManager() = default;
            ModuleManager(const ModuleManager&) = delete;
            ModuleManager& operator=(const ModuleManager&) = delete;
    };
}
