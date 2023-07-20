cmake_minimum_required(VERSION 3.16)

set(VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cutil)

option(CUTIL_TESTS "Enable testing" OFF)

file(GLOB
    SRC
    src/map.c
    src/vector.c
    src/string.c
    src/stack.c
)

file(GLOB
    PUBLIC_HEADERS
    include/cutil.h
)

file(GLOB
    PRIVATE_HEADERS
    include/cutil/map.h
    include/cutil/vector.h
    include/cutil/string.h
    include/cutil/stack.h
)

add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        include
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    cutil.cmake
    VERSION ${VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES ${PUBLIC_HEADERS} DESTINATION "include/")
install(FILES ${PRIVATE_HEADERS} DESTINATION "include/cutil")
install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(CUTIL_TESTS)
    add_subdirectory(check)
endif()

