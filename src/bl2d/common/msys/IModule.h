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
    };
}
