#pragma once

#include "cpputill/shared_mutex.hpp"

namespace cpputill 
{

class SharedLockGuard 
{
public:
    // Constructor: Acquires a shared lock on the given mutex.
    explicit SharedLockGuard(SharedMutex& mutex);

    // Destructor: Releases the shared lock if it is still held.
    ~SharedLockGuard();

    // Disables copy constructor to prevent multiple ownership of the same lock.
    SharedLockGuard(const SharedLockGuard&) = delete;

    // Disables copy assignment operator to prevent multiple ownership of the same lock.
    SharedLockGuard& operator=(const SharedLockGuard&) = delete;

    // Releases the shared lock manually.
    void unlock();

private:
    SharedMutex& m_mutex; // Reference to the shared mutex.
    bool m_locked;        // Tracks whether the lock is currently held.
};

} // namespace cpputill
