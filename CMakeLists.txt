cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(includes libs/libft)

set(READ_LINE_SRCS
        src/read_line/read_line.c)

set(PARSE_COMMANDS src/parse_commands/parse_commands.c )

set(EXEC_ALL_COMMANDS src/exec_all_commands/exec_all_commands.c)

set(CLEAR_COMMAND_LINE src/clear_command_line/clear_command_line.c)

add_executable(minishell
        ${READ_LINE_SRCS}
        ${PARSE_COMMANDS}
        ${EXEC_ALL_COMMANDS}
        ${CLEAR_COMMAND_LINE}

        main.c)

target_link_libraries(minishell ${CMAKE_SOURCE_SIR}/libs/libft)