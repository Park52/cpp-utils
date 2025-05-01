#pragma once

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <pthread.h>
#endif

namespace cpputill 
{

class SharedMutex 
{
public:
    SharedMutex();
    ~SharedMutex();

    void lock();            // exclusive lock
    void unlock();
    void lock_shared();     // shared/read lock
    void unlock_shared();

    bool try_lock();
    bool try_lock_shared();

private:
#if defined(_WIN32)
    SRWLOCK m_lock;
#else
    pthread_rwlock_t m_lock;
#endif
};

} // namespace cpputill
