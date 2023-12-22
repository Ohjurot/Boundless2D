#include "ThreadWindows.h"

bl2d::platform::ThreadWindows::ThreadWindows(ThreadFunction function) :
    m_function(function)
{
    DWORD threadId = -1;
    m_threadHandle = CreateThread(nullptr, 0, &ThreadWindows::ThreadProc, this, CREATE_SUSPENDED, &threadId);
    m_threadId = threadId;
    if (m_threadHandle == NULL)
    {
        throw BL2D_BUILD_WINDOWS_EXCEPTION("CreateThread", GetLastError())
            .Build();
    }
}

bl2d::platform::ThreadWindows::~ThreadWindows()
{
    // Reactivate thread if it is paused
    if (m_state == ThreadState::Paused)
    {
        Start();
    }

    // Now terminate the thread (will try it gracefully first, only when running)
    Terminate();

    if (m_threadHandle)
    {
        CloseHandle(m_threadHandle);
    }
}

void bl2d::platform::ThreadWindows::Start()
{
    if (m_state == ThreadState::Created || m_state == ThreadState::Paused)
    {
        auto result = ResumeThread(m_threadHandle);
        if (result == -1)
        {
            throw BL2D_BUILD_WINDOWS_EXCEPTION("ResumeThread", GetLastError())
                .Build();
        }
        m_state = ThreadState::Running;
    }
}

void bl2d::platform::ThreadWindows::Pause()
{
    if (m_state == ThreadState::Running)
    {
        auto result = SuspendThread(m_threadHandle);
        if (result == -1)
        {
            throw BL2D_BUILD_WINDOWS_EXCEPTION("SuspendThread", GetLastError())
                .Build();
        }
        m_state = ThreadState::Paused;
    }
}

void bl2d::platform::ThreadWindows::Stop()
{
    m_stopCookie = true;
}

void bl2d::platform::ThreadWindows::Terminate()
{
    // Gracefully try
    if (m_state == ThreadState::Running)
    {
        Stop();
        WaitForSingleObject(m_threadHandle, 10000);
    }

    // Forcefully stop
    if (m_state == ThreadState::Running)
    {
        TerminateThread(m_threadHandle, -1);
        m_terminationCause = "The thread was terminated using the Terminate() function";
        m_state = ThreadState::Terminated;
    }
}

bool bl2d::platform::ThreadWindows::Wait(size_t max)
{
    if (m_state == ThreadState::Running)
    {
        return WaitForSingleObject(m_threadHandle, max) == WAIT_OBJECT_0;
    }
    else if (m_state == ThreadState::Created || m_state == ThreadState::Paused)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bl2d::platform::ThreadId bl2d::platform::ThreadWindows::GetTID() const
{
    return m_threadId;
}

bl2d::platform::ThreadReturnCode bl2d::platform::ThreadWindows::GetReturnCode() const
{
    return m_returnCode;
}

bl2d::platform::ThreadState bl2d::platform::ThreadWindows::GetState() const
{
    return m_state;
}

const std::string& bl2d::platform::ThreadWindows::GetTerminationCause() const
{
    return m_terminationCause;
}

DWORD bl2d::platform::ThreadWindows::ThreadProcSelf()
{
    m_state = ThreadState::Running;
    try
    {
        m_returnCode = m_function(*this, m_stopCookie);
        m_state = ThreadState::Finished;
    }
    catch (const std::exception& ex)
    {
        m_terminationCause = ex.what();
        m_state = ThreadState::Terminated;
    }

    return 0;
}

DWORD WINAPI bl2d::platform::ThreadWindows::ThreadProc(_In_ LPVOID lpParameter)
{
    ThreadWindows* self = (ThreadWindows*)lpParameter;
    return self->ThreadProcSelf();
}
