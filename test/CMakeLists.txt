# 테스트 타겟 생성

set(TEST_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/test_shared_mutex.hpp
)

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_shared_mutex.cpp
)

add_executable(shared_mutex_test
    ${TEST_HEADERS}
    ${TEST_SOURCES}
)

target_include_directories(shared_mutex_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}       # test/
)

# 링크 라이브러리 설정
target_link_libraries(shared_mutex_test
    cpputill
    GTest::gtest
    GTest::gtest_main
)

# Visual Studio 솔루션 정리를 위한 그룹 지정
source_group("Header Files" FILES ${TEST_HEADERS})
source_group("Source Files" FILES ${TEST_SOURCES})

# 테스트 등록
add_test(NAME SharedMutexTest COMMAND shared_mutex_test)
