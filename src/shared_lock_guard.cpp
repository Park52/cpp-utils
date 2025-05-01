#include "cpputill/shared_lock_guard.hpp"

namespace cpputill 
{

SharedLockGuard::SharedLockGuard(SharedMutex& mutex)
    : m_mutex(mutex)
	, m_locked(true) 	
{
    m_mutex.lock_shared();
}

SharedLockGuard::~SharedLockGuard() {
    if (m_locked) {
        m_mutex.unlock_shared();
    }
}

} // namespace cpputill
