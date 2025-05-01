#include "cpputill/shared_mutex.hpp"

namespace cpputill 
{

SharedMutex::SharedMutex() 
{
#if defined(_WIN32)
    InitializeSRWLock(&m_lock);
#else
    pthread_rwlock_init(&m_lock, nullptr);
#endif
}

SharedMutex::~SharedMutex() 
{
#if !defined(_WIN32)
    pthread_rwlock_destroy(&m_lock);
#endif
}

void SharedMutex::lock() 
{
#if defined(_WIN32)
    AcquireSRWLockExclusive(&m_lock);
#else
    pthread_rwlock_wrlock(&m_lock);
#endif
}

void SharedMutex::unlock() 
{
#if defined(_WIN32)
    ReleaseSRWLockExclusive(&m_lock);
#else
    pthread_rwlock_unlock(&m_lock);
#endif
}

void SharedMutex::lock_shared() 
{
#if defined(_WIN32)
    AcquireSRWLockShared(&m_lock);
#else
    pthread_rwlock_rdlock(&m_lock);
#endif
}

void SharedMutex::unlock_shared() 
{
#if defined(_WIN32)
    ReleaseSRWLockShared(&m_lock);
#else
    pthread_rwlock_unlock(&m_lock);
#endif
}

bool SharedMutex::try_lock() 
{
#if defined(_WIN32)
    return TryAcquireSRWLockExclusive(&m_lock);
#else
    return pthread_rwlock_trywrlock(&m_lock) == 0;
#endif
}

bool SharedMutex::try_lock_shared() 
{
#if defined(_WIN32)
    return TryAcquireSRWLockShared(&m_lock);
#else
    return pthread_rwlock_tryrdlock(&m_lock) == 0;
#endif
}

} // namespace cpputill
