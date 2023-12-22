#pragma once

#include <i.bl2d.platform/IThread.h>

namespace bl2d::platform
{
    /*!
     * @brief Class responsible for creating threads and getting information about the system
     * 
     * TO BE RETRIVED VIA IOC
    */
    class IThreadFactory
    {
        public:
            virtual ~IThreadFactory() = default;

            /*!
             * @brief Returns the number of threads the system can run simultaneously
             * @return Number of threads
            */
            virtual size_t GetSystemThreadCount() = 0;

            /*!
             * @brief Creates a thread that will be suspended
             * @param function Function that the thread shall execute as soon as it's running
             * @return Pointer to the created thread
            */
            virtual ThreadPtr CreateSuspendedThread(const ThreadFunction& function) = 0;
    };
}
