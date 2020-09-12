cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(includes libs/libft)

set(READ_LINE_SRCS
        src/read_line.c
        )

add_executable(minishell
        ${}
        main.c)

target_link_libraries(minishell ${CMAKE_SOURCE_SIR}/libs/libft)
