cmake_minimum_required(VERSION 3.5)

project(ip_filter  VERSION 1.0.0)
add_executable(ip_filter ip_filter.cpp)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE /W4)
else ()
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in" 
    "${CMAKE_BINARY_DIR}/version.h"          
)
target_include_directories(ip_filter PRIVATE "${CMAKE_BINARY_DIR}")