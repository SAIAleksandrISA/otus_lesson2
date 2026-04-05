cmake_minimum_required(VERSION 3.5)

project(ip_filter)

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