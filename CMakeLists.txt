cmake_minimum_required(VERSION 3.14)
project(cpp-utill LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- 유틸리티 라이브러리 구성 ----

# 헤더 및 소스 파일 나열
set(HEADER_FILES
    include/cpputill/shared_mutex.hpp
    include/cpputill/shared_lock_guard.hpp
    include/cpputill/unique_lock_guard.hpp
)

set(SOURCE_FILES
    src/shared_mutex.cpp
    src/shared_lock_guard.cpp
    src/unique_lock_guard.cpp
)

add_library(cpputill
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

# include 디렉토리 연결
target_include_directories(cpputill
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# ---- Visual Studio UX 개선용 그룹 정리 ----

source_group(TREE "${CMAKE_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE "${CMAKE_SOURCE_DIR}/src"     PREFIX "Source Files" FILES ${SOURCE_FILES})

# ---- GoogleTest 자동 다운로드 ----

include(FetchContent)
# ✔️ 테스트 프로젝트도 DLL CRT (MD) 사용
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# ---- 테스트 추가 ----

enable_testing()
add_subdirectory(test)
