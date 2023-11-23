#pragma once

#include <bl2d/common/ioc/IoCRegistrations.h>
#include <bl2d/common/msys/ModuleDescription.h>

namespace bl2d
{
    /*!
     * @brief Interface for API-Implementation modules
    */
    class IModule
    {
        public:
            virtual ~IModule() = default;

            /*!
             * @brief Retrieves the modules description
             * @return Const ref to descriptor
            */
            virtual const ModuleDescription& GetDesc() const = 0;

            /*!
             * @brief Called when the module should setup it's implementation
             * @param registrar IoCRegistration endpoint
            */
            virtual void Register(IoCRegistrations& registrar) = 0;

            /*!
             * @brief Called after modules are registered while loading
             *
             * No object or module communication allowed
             * (before modules OnLoad(..))
            */
            virtual void OnLoad() {};

            /*!
             * @brief Called after all modules are loaded and ready during application load
             *
             * Allowed: App --> Object; App --> Module
             * (after modules OnInit(..))
            */
            virtual void OnInit() {};

            /*!
             * @brief Called before objects are destroyed during shutdown
             *
             * Allowed: App --> Object; App --> Module
             * (before modules OnShutdown(..))
            */
            virtual void OnShutdown() {};

            /*!
             * @brief Called after all modules are unloaded
             *
             * No object or module communication allowed
             * (after modules OnUnload(..))
            */
            virtual void OnUnload() {};
    };
}
