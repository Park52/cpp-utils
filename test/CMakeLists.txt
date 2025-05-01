# 테스트 타겟 생성
add_executable(shared_mutex_test
    test_shared_mutex.cpp
)

# 링크 라이브러리 설정
target_link_libraries(shared_mutex_test
    cpputill
    gtest
    gtest_main
)

# 테스트 등록
add_test(NAME SharedMutexTest COMMAND shared_mutex_test)
