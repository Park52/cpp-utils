#include <gtest/gtest.h>
#include "test_shared_mutex.hpp"
#include "cpputill/shared_mutex.hpp"
#include "cpputill/shared_lock_guard.hpp"
#include "cpputill/unique_lock_guard.hpp"

#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <iostream>

bool LargeKey::operator<(const LargeKey& other) const
{
    int cmp = std::strcmp(name, other.name);
    return cmp == 0 ? id < other.id : cmp < 0;
}

LargeKey makeKey(int i)
{
    LargeKey key;
    std::snprintf(key.name, sizeof(key.name), "Key%05d", i % 100);
    key.id = i % 100;
    return key;
}

LargeValue makeValue(int i)
{
    LargeValue val;
    std::snprintf(val.description, sizeof(val.description), "Value%05d", i);
    for (uint32_t j = 0; j < 8; ++j)
    {
        val.metrics[j] = i * 0.1 + j;
    }
    return val;
}

void run_std_mutex() 
{
    std::mutex mtx;

    auto reader = [](std::mutex& mtx, int& shared_value, int& dummy_sum) 
    {
        for (int i = 0; i < 500000; ++i)
        {
            std::lock_guard<std::mutex> lock(mtx);
            dummy_sum += shared_value;
        }
    };

    auto writer = [](std::mutex& mtx, int& shared_value, int&) 
    {
        for (int i = 0; i < 500000; ++i)
        {
            std::lock_guard<std::mutex> lock(mtx);
            ++shared_value;
        }
    };

    benchmark("[std::mutex]", mtx, reader, writer);
}

void run_shared_mutex() 
{
    cpputill::SharedMutex smtx;

    auto reader = [](cpputill::SharedMutex& smtx, int& shared_value, int& dummy_sum) 
    {
        for (int i = 0; i < 500000; ++i) 
        {
            cpputill::SharedLockGuard lock(smtx);
            dummy_sum += shared_value;
        }
    };

    auto writer = [](cpputill::SharedMutex& smtx, int& shared_value, int&) 
    {
        for (int i = 0; i < 500000; ++i)
        {
            cpputill::UniqueLockGuard lock(smtx);
            ++shared_value;
        }
    };

    benchmark("[SharedMutex]", smtx, reader, writer);
}

void run_std_mutex_largeData()
{
    std::mutex mtx;

    auto reader = [](std::mutex& mtx, std::map<LargeKey, LargeValue>& shared_value)
    {
        for (uint32_t i = 0; i < 500000; ++i)
        {
            std::lock_guard<std::mutex> lock(mtx);
            auto it = shared_value.find(makeKey(i));
            if (it != shared_value.end())
            {
                volatile double x = it->second.metrics[0];
            }
        }
    };

    auto writer = [](std::mutex& mtx, std::map<LargeKey, LargeValue>& shared_value)
    {
        for (int i = 0; i < 500000; ++i)
        {
            std::lock_guard<std::mutex> lock(mtx);
            shared_value[makeKey(i)] = makeValue(i);
        }
    };

    benchmarklargeData("[std::mutex_largeData]", mtx, reader, writer);
}

void run_shared_mutex_largeData()
{
    cpputill::SharedMutex smtx;

    auto reader = [](cpputill::SharedMutex& smtx, std::map<LargeKey, LargeValue>& shared_value)
    {
        for (int i = 0; i < 500000; ++i)
        {
            cpputill::SharedLockGuard lock(smtx);
            const auto it = shared_value.find(makeKey(i));
            if (it != shared_value.end())
            {
                volatile double x = it->second.metrics[0];
            }
        }
    };

    auto writer = [](cpputill::SharedMutex& smtx, std::map<LargeKey, LargeValue>& shared_value)
    {
        for (int i = 0; i < 500000; ++i)
        {
            cpputill::UniqueLockGuard lock(smtx);
            shared_value[makeKey(i)] = makeValue(i);
        }
    };

    benchmarklargeData("[SharedMutex_largeData]", smtx, reader, writer);
}

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

TEST(SharedMutexTest, BenchMarkstdMutex)
{
    run_std_mutex();
    SUCCEED();
}

TEST(SharedMutexTest, BenchMarkSharedMutex)
{
    run_shared_mutex();
    SUCCEED();
}

TEST(SharedMutexTest, BenchMarkstdMutexLargeData)
{
    run_std_mutex_largeData();
    SUCCEED();
}

TEST(SharedMutexTest, BenchMarkSharedMutexLargeData)
{
    run_shared_mutex_largeData();
    SUCCEED();
}