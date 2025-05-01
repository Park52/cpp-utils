#include "cpputill/unique_lock_guard.hpp"

namespace cpputill {

UniqueLockGuard::UniqueLockGuard(SharedMutex& mutex)
    : m_mutex(mutex)
	, m_locked(true) 
{
    m_mutex.lock();
}

UniqueLockGuard::~UniqueLockGuard() 
{
    if (m_locked) 
	{
        m_mutex.unlock();
    }
}

} // namespace cpputill
