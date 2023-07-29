[![C/C++ CI](https://github.com/caaallum/cutil/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/caaallum/cutil/actions/workflows/c-cpp.yml)
# CUtil

A collection of utilities and data structures for C99

## Usage
```cmake
include(FetchContent)
FetchContent_Declare(cutil
    GIT_REPOSITORY      https://github.com/caaallum/cutil.git
    GIT_SHALLOW         TRUE
)
FetchContent_MakeAvailable(cutil)

target_link_libraries(${PROJECT_NAME} PRIVATE cutil)
```