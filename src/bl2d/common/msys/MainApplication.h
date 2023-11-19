#pragma once

#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/ioc/IoCRegistrations.h>
#include <bl2d/common/msys/ModuleManager.h>
#include <bl2d/common/msys/MainApplicationArguments.h>

namespace bl2d
{
    /*!
     * @brief Base class for applications.
     *
     * IoC and msys powerded!
    */
    class MainApplication
    {
        public:
            using IMainApplicationArguments = ::bl2d::IMainApplicationArguments;

        public:
            MainApplication();
            virtual ~MainApplication();

            virtual int Run(const IMainApplicationArguments& args);

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

            /*!
             * @brief Retrive the IoC stack for the application
             * @return L0 IoC-Stakc (Application Level)
            */
            inline IoCStack& GetIoC() { return ioc; }

        protected:
            IoCStack ioc;

        private:
            /*!
                 * @brief A call to this function will load all modules and initialize msys and ioc
                */
            void Init();

            /*!
             * @brief A call to this function will shutdown msys, ioc and unloads modules
            */
            void Shutdown();
    };
}
