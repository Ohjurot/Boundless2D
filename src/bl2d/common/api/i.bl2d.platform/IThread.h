#pragma once

#include <memory>
#include <string>
#include <functional>

namespace bl2d::platform
{
    class IThread;

    /*!
     * @brief Pointer to a thread
    */
    using ThreadPtr = std::shared_ptr<IThread>;

    /*!
     * @brief Return value of thread
    */
    using ThreadReturnCode = size_t;

    /*!
     * @brief Identifier of the thread
    */
    using ThreadId = size_t;

    /*!
     * @brief Base function of a thread
    */
    using ThreadFunction = std::function<ThreadReturnCode(IThread& self, const bool& shouldStop)>;

    /*!
     * @brief State of thread
    */
    enum class ThreadState
    {
        /*!
         * @brief The thread was created but not yet stated
        */
        Created,

        /*!
         * @brief The thread is running
        */
        Running,

        /*!
         * @brief The thread is paused
        */
        Paused,

        /*!
         * @brief The thread has finished
        */
        Finished,

        /*!
         * @brief The thread was forcefully terminated
        */
        Terminated,
    };

    /*!
     * @brief Implementation of a platform thread
     * 
     * TO BE RETRIVED VIA "IThreadFactory"
    */
    class IThread
    {
        public:
            virtual ~IThread() = default;

            /*!
             * @brief Starts (resumes) thread execution
            */
            virtual void Start() = 0;
            
            /*!
             * @brief Pauses a thread
            */
            virtual void Pause() = 0;

            /*!
             * @brief Request the thread to stop gracefully
            */
            virtual void Stop() = 0;
            
            /*!
             * @brief Forcefully terminates a thread
            */
            virtual void Terminate() = 0;

            /*!
             * @brief Waits for the thread terminating
             * @param max Maximum number of ms to wait
             * @return True if the thread terminated. False on wait timeout.
            */
            virtual bool Wait(size_t max) = 0;

            /*!
             * @brief Gets the return code
             * @return -1 as long as running otherwise the return code of the thread
            */
            virtual ThreadReturnCode GetReturnCode() const = 0;

            /*!
             * @brief Retrieves the threads identifier
             * @return Thread ID
            */
            virtual ThreadId GetTID() const = 0;

            /*!
             * @brief Returns the current state of the thread
             * @return State
            */
            virtual ThreadState GetState() const = 0;

            /*!
             * @brief Gets information on why the thread was terminated
             * @return Information as string (exception)
            */
            virtual const std::string& GetTerminationCause() const = 0;
    }; 
}
