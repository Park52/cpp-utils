#pragma once
#include "shared_mutex.hpp"

namespace cpputill 
{

class UniqueLockGuard 
{
public:
    explicit UniqueLockGuard(SharedMutex& mutex);
    ~UniqueLockGuard();

    UniqueLockGuard(const UniqueLockGuard&) = delete;
    UniqueLockGuard& operator=(const UniqueLockGuard&) = delete;

private:
    SharedMutex& m_mutex;
    bool m_locked;
};

} // namespace cpputill
