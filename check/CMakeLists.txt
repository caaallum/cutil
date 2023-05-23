cmake_minimum_required(VERSION 3.16)

enable_testing()

include(FetchContent)
FetchContent_Declare(check
    URL https://github.com/libcheck/check/releases/download/0.15.2/check-0.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(check)

add_custom_target(test
    COMMAND ctest
    DEPENDS check_map check_vector check_string check_stack
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/check
)

macro(cutil_add_test name file)
    add_executable(${name} ${file})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${name} 
        PRIVATE check
        PRIVATE cutil
    )
    add_test(${name} ${name})
endmacro()

cutil_add_test(check_map check_map.c)
cutil_add_test(check_vector check_vector.c)
cutil_add_test(check_string check_string.c)
cutil_add_test(check_stack check_stack.c)
