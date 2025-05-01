#include <gtest/gtest.h>
#include "cpputill/shared_mutex.hpp"
#include "cpputill/shared_lock_guard.hpp"
#include "cpputill/unique_lock_guard.hpp"

TEST(SharedMutexTest, SharedLockGuardWorks) 
{
    cpputill::SharedMutex mutex;
    cpputill::SharedLockGuard lock(mutex);
    SUCCEED(); // 테스트 통과 시도
}

TEST(SharedMutexTest, UniqueLockGuardWorks) 
{
    cpputill::SharedMutex mutex;
    cpputill::UniqueLockGuard lock(mutex);
    SUCCEED();
}

TEST(SharedMutexTest, TryLockShared) 
{
    cpputill::SharedMutex mutex;
    EXPECT_TRUE(mutex.try_lock_shared());
    mutex.unlock_shared();
}

TEST(SharedMutexTest, TryLockExclusive) 
{
    cpputill::SharedMutex mutex;
    EXPECT_TRUE(mutex.try_lock());
    mutex.unlock();
}
