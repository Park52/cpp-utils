#include "cpputill/shared_lock_guard.hpp"

namespace cpputill 
{

// Constructor: Acquires a shared lock on the given mutex.
SharedLockGuard::SharedLockGuard(SharedMutex& mutex)
    : m_mutex(mutex), m_locked(true)
{
    m_mutex.lock_shared();
}

// Destructor: Releases the shared lock if it is still held.
SharedLockGuard::~SharedLockGuard()
{
    if (m_locked)
        m_mutex.unlock_shared();
}

// Releases the shared lock manually.
void SharedLockGuard::unlock()
{
    if (m_locked)
    {
        m_mutex.unlock_shared();
        m_locked = false;
    }
}

} // namespace cpputill
