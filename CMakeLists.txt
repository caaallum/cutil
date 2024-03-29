cmake_minimum_required(VERSION 3.16)

set(VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cutil)

option(CUTIL_TESTS "Enable testing" OFF)
option(CUTIL_DOCS "Build cutil docs" OFF)

file(GLOB
    SRC
    src/map.c
    src/vector.c
    src/string.c
    src/stack.c
    src/csv.c
    src/linked_list.c
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
    include/cutil/csv.h
    include/cutil/linked_list.c
)

add_library(${PROJECT_NAME} ${SRC} ${PRIVATE_HEADERS} ${PUBLIC_HEADERS})

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

if (CUTIL_DOCS)
    find_package(Doxygen)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(build-docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
endif()

