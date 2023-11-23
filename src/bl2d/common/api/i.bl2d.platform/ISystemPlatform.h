#pragma once

namespace bl2d::platform
{
    /*!
     * @brief Indicates the kind of platform
    */
    enum class PlatformKind
    {
        /*!
         * @brief Windows like operating system
        */
        Windows,

        /*!
         * @brief Linux distribution
        */
        Linux
    };

    /*!
     * @brief Information about the platform
    */
    struct PlatformInfo
    {
        PlatformKind kind;
        const char* name;
        const char* version;
    };

    /*!
     * @brief Interface for platforms
    */
    class ISystemPlatform
    {
        public:
            virtual ~ISystemPlatform() = default;
            
            /*!
             * @brief Initializes all platform services
            */
            virtual void Init() = 0;

            /*!
             * @brief Shutdown all platform services
            */
            virtual void Shutdown() = 0;

            /*!
             * @brief Retrieves information about the system platform
             * @return Reference to platform info
            */
            virtual const PlatformInfo& GetInfo() const = 0;

    };
}
