// test_shared_mutex.hpp

#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

struct LargeKey
{
    char name[64];
    int id;

    bool operator<(const LargeKey& other) const;
};

struct LargeValue
{
    char description[128];
    double metrics[8];
};

LargeKey makeKey(int i);
LargeValue makeValue(int i);

template <typename LockType, typename ReaderFunc, typename WriterFunc>
void benchmark(const std::string& label, LockType& lock, ReaderFunc reader_func, WriterFunc writer_func)
{
    int shared_value = 0;
    int dummy_sum = 0;

    const auto start = std::chrono::high_resolution_clock::now();
    std::thread writer(writer_func, std::ref(lock), std::ref(shared_value), std::ref(dummy_sum));

    std::vector<std::thread> readers;
    for (int i = 0; i < 3; ++i)
    {
        readers.emplace_back(reader_func, std::ref(lock), std::ref(shared_value), std::ref(dummy_sum));
    }

    for (auto& t : readers)
    {
        t.join();
    }
    writer.join();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << label << ": " << ms << " ms\n";
}

template <typename LockType, typename ReaderFunc, typename WriterFunc>
void benchmarklargeData(const std::string& label, LockType& lock, ReaderFunc reader_func, WriterFunc writer_func)
{
    std::map<LargeKey, LargeValue> mapstruct;
    mapstruct.clear();
    for (uint32_t i = 0; i < 100; ++i)
    {
        mapstruct[makeKey(i)] = makeValue(i);
    }

    const auto start = std::chrono::high_resolution_clock::now();
    std::thread writer(writer_func, std::ref(lock), std::ref(mapstruct));

    std::vector<std::thread> readers;
    for (int i = 0; i < 3; ++i)
    {
        readers.emplace_back(reader_func, std::ref(lock), std::ref(mapstruct));
    }

    for (auto& t : readers)
    {
        t.join();
    }
    writer.join();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << label << ": " << ms << " ms\n";
}