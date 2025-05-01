#pragma once
#include "shared_mutex.hpp"

namespace cpputill 
{

class SharedLockGuard 
{
public:
    explicit SharedLockGuard(SharedMutex& mutex);
    ~SharedLockGuard();

    SharedLockGuard(const SharedLockGuard&) = delete;
    SharedLockGuard& operator=(const SharedLockGuard&) = delete;

private:
    SharedMutex& m_mutex;
    bool m_locked;
};

} // namespace cpputill
