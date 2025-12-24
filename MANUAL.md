# 1. 프로그램 설치
1. Git 설치
2. VSCode, C++, CMake 확장자 설치
3. SFML 설치
    - WinLibs UCRT 14.2.0 (64-bit)
    - GCC 14.2.0 MinGW (SEH) (UCRT)
    - 환경변수 패스 추가 (환경변수 패스가 무엇인지 설명)

# 2. 프로젝트 준비
1. CMake 템플레이트 프로젝트 Git Clone
2. CMake 어느정도 해설(이게 무엇인가, 언제쯤 자세하게 배우나 등)
3. 첫 SFML 프로그램 작성
4. 실행
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release # Linux
cmake -S . -B build -G "MinGW Makefiles" # Windows
cmake --build build --config Release
```
