# cpp-utill

C++14 기반 유틸리티 라이브러리입니다.  
학습과 유닛 테스트를 병행하며, 멀티플랫폼 환경을 고려해 개발됩니다.

## ✅ 첫 번째 구현
- `shared_mutex`: Windows (SRWLOCK) / Linux (pthread_rwlock_t) 지원

## 💡 컴파일 방법

```bash
mkdir build && cd build
cmake ..
make
ctest
