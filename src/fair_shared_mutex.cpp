#include "cpputill/fair_shared_mutex.hpp"

namespace cpputill 
{

// Constructor: Initializes the FairSharedMutex.
FairSharedMutex::FairSharedMutex()
    : m_writer_active(false), m_active_readers(0), m_waiting_writers(0)
{}

// Destructor: Cleans up resources.
FairSharedMutex::~FairSharedMutex()
{}

// Locks the mutex exclusively for write access.
void FairSharedMutex::lock()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    ++m_waiting_writers;
    m_cv.wait(lock, [this]() {
        return !m_writer_active && m_active_readers == 0;
    });
    --m_waiting_writers;
    m_writer_active = true;
}

// Unlocks the mutex from exclusive write access.
void FairSharedMutex::unlock()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_writer_active = false;
    m_cv.notify_all();
}

// Locks the mutex for shared read access.
void FairSharedMutex::lock_shared()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this]() {
        return !m_writer_active && m_waiting_writers == 0;
    });
    ++m_active_readers;
}

// Unlocks the mutex from shared read access.
void FairSharedMutex::unlock_shared()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    --m_active_readers;
    if (m_active_readers == 0)
        m_cv.notify_all();
}

// Tries to lock the mutex exclusively for write access without blocking.
// Returns true if the lock was acquired, false otherwise.
bool FairSharedMutex::try_lock()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_writer_active && m_active_readers == 0) 
    {
        m_writer_active = true;
        return true;
    }
    return false;
}

// Tries to lock the mutex for shared read access without blocking.
// Returns true if the lock was acquired, false otherwise.
bool FairSharedMutex::try_lock_shared()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_writer_active && m_waiting_writers == 0) 
    {
        ++m_active_readers;
        return true;
    }
    return false;
}

} // namespace cpputill
