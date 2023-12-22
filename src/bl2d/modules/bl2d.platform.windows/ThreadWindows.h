#pragma once

#include <i.bl2d.platform/IThread.h>

#include <bl2d/common/boot/os.h>

#include <bl2d.platform.windows/auxiliary/util/HrExceptionFormater.h>

namespace bl2d::platform
{
    class ThreadWindows : public IThread
    {
        public:
            ThreadWindows(ThreadFunction function);
            ~ThreadWindows() override;

            void Start() override;
            void Pause() override;
            void Stop() override;
            void Terminate() override;
            bool Wait(size_t max) override;
            ThreadId GetTID() const override;
            ThreadReturnCode GetReturnCode() const override;
            ThreadState GetState() const override;
            const std::string& GetTerminationCause() const override;

        private:
            DWORD ThreadProcSelf();
            static DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter);

        private:
            ThreadFunction m_function;
            bool m_stopCookie = false;

            HANDLE m_threadHandle = NULL;

            ThreadState m_state = ThreadState::Created;
            ThreadReturnCode m_returnCode = -1;
            ThreadId m_threadId = 0;
            std::string m_terminationCause;
    };
}
