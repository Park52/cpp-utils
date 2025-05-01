# cpp-utill

C++14 기반 유틸리티 라이브러리입니다.  
멀티플랫폼 환경에서 사용할 수 있는 동기화 도구(shared_mutex 등)와 RAII 유틸리티를 직접 구현하고, Google Test를 통해 안정성을 검증합니다.

---

## ✅ Features

- `SharedMutex`: C++14에서 사용할 수 있는 `std::shared_mutex` 대체 구현  
  - Windows: `SRWLOCK` 기반  
  - POSIX: `pthread_rwlock_t` 기반
- `SharedLockGuard`: read 락 전용 RAII 클래스
- `UniqueLockGuard`: write 락 전용 RAII 클래스
- `try_lock`, `try_lock_shared` 지원
- GoogleTest 기반 단위 테스트 구성
- CMake 기반 크로스플랫폼 빌드 구성

---

## 🛠️ Build Instructions

`cpp-utill`는 CMake 기반 프로젝트로 Windows와 Linux 모두에서 쉽게 빌드할 수 있습니다.

---

### 🪟 Windows (PowerShell 기준)

```powershell
# 기존 빌드 폴더 제거 및 생성
rd /s /q build
mkdir build
cd build

# Visual Studio 2022 기준 설정 및 빌드
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Debug

# 테스트 실행
ctest -C Debug
```

### 🪟 Linux (Ubuntu 기준)
```
# 필수 도구 설치
sudo apt update
sudo apt install build-essential cmake git -y

# 프로젝트 클론 및 빌드
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)

# 테스트 실행
ctest
```