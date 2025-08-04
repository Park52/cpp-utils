#include "cpputill/shared_mutex.hpp"

namespace cpputill 
{

// Constructor: Initializes the shared mutex based on the platform.
SharedMutex::SharedMutex() 
{
#if defined(_WIN32)
    InitializeSRWLock(&m_lock); // Windows-specific initialization
#else
    pthread_rwlock_init(&m_lock, nullptr); // POSIX-specific initialization
#endif
}

// Destructor: Cleans up resources for POSIX platforms.
SharedMutex::~SharedMutex() 
{
#if !defined(_WIN32)
    pthread_rwlock_destroy(&m_lock); // POSIX-specific cleanup
#endif
}

// Locks the mutex exclusively for write access.
void SharedMutex::lock() 
{
#if defined(_WIN32)
    AcquireSRWLockExclusive(&m_lock); // Windows-specific exclusive lock
#else
    pthread_rwlock_wrlock(&m_lock); // POSIX-specific exclusive lock
#endif
}

// Unlocks the mutex from exclusive write access.
void SharedMutex::unlock() 
{
#if defined(_WIN32)
    ReleaseSRWLockExclusive(&m_lock); // Windows-specific unlock
#else
    pthread_rwlock_unlock(&m_lock); // POSIX-specific unlock
#endif
}

// Locks the mutex for shared read access.
void SharedMutex::lock_shared() 
{
#if defined(_WIN32)
    AcquireSRWLockShared(&m_lock); // Windows-specific shared lock
#else
    pthread_rwlock_rdlock(&m_lock); // POSIX-specific shared lock
#endif
}

// Unlocks the mutex from shared read access.
void SharedMutex::unlock_shared() 
{
#if defined(_WIN32)
    ReleaseSRWLockShared(&m_lock); // Windows-specific shared unlock
#else
    pthread_rwlock_unlock(&m_lock); // POSIX-specific unlock
#endif
}

// Tries to lock the mutex exclusively for write access without blocking.
// Returns true if the lock was acquired, false otherwise.
bool SharedMutex::try_lock() 
{
#if defined(_WIN32)
    return TryAcquireSRWLockExclusive(&m_lock); // Windows-specific try lock
#else
    return pthread_rwlock_trywrlock(&m_lock) == 0; // POSIX-specific try lock
#endif
}

// Tries to lock the mutex for shared read access without blocking.
// Returns true if the lock was acquired, false otherwise.
bool SharedMutex::try_lock_shared() 
{
#if defined(_WIN32)
    return TryAcquireSRWLockShared(&m_lock); // Windows-specific try shared lock
#else
    return pthread_rwlock_tryrdlock(&m_lock) == 0; // POSIX-specific try shared lock
#endif
}

} // namespace cpputill
