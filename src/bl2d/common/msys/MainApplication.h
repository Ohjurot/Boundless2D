#pragma once

#include <bl2d/common/ioc/IoCStack.h>
#include <bl2d/common/ioc/IoCRegistrations.h>
#include <bl2d/common/msys/ModuleManager.h>
#include <bl2d/common/msys/MainApplicationArguments.h>

#include <bl2d/common/util/Exception.h>

#include <i.bl2d.platform/ISystemPlatform.h>

namespace bl2d
{
    /*!
     * @brief Base class for applications.
     *
     * IoC and msys powered!
    */
    class MainApplication
    {
        public:
            using IMainApplicationArguments = ::bl2d::IMainApplicationArguments;
            using Exception = ::bl2d::util::Exception;

        public:
            MainApplication();
            virtual ~MainApplication();

            int RunSafe(const IMainApplicationArguments& args);

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
             * (before modules OnInit(..))
            */
            virtual void OnInit();

            /*!
             * @brief Called before objects are destroyed during shutdown
             * 
             * Allowed: App --> Object; App --> Module
             * (after modules OnShutdown(..)) 
            */
            virtual void OnShutdown();

            /*!
             * @brief Called after all modules are unloaded
             * 
             * No object or module communication allowed
             * (after modules OnUnload(..)) 
            */
            virtual void OnUnload() {};

            /*!
             * @brief Exception callback
             * @param ex Exceptions code
            */
            virtual void OnException(const Exception& ex);

            /*!
             * @brief Retrive the IoC stack for the application
             * @return L0 IoC-Stakc (Application Level)
            */
            inline IoCStack& GetIoC() { return ioc; }

            inline bool IsInitialized() const { return m_isInitialized; }

        protected:
            IoCStack ioc;

        private:
            bool m_isInitialized = false;

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
