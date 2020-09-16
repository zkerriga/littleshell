cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(includes/
                    libs/libft/
                    src/classes/environment/
                    src/classes/word_work)

set(READ_LINE_SRCS
        src/read_line/read_line.c)

set(PARSE_COMMANDS
        src/parse_commands/parse_commands.c
        src/parse_commands/separate_commands.c
        src/parse_commands/parse_single_command.c src/classes/word_work/word_work_new.c)

set(EXEC_ALL_COMMANDS
        src/exec_all_commands/exec_all_commands.c)

set(CLEAR_COMMAND_LINE
        src/clear_command_line/clear_command_line.c)

set(ENVIRONMENT
        src/classes/environment/environment_new.c
        src/classes/environment/environment_del.c
        src/classes/environment/environment_add.c
        src/classes/environment/environment_print.c
        src/classes/environment/environment_remove.c
        src/classes/environment/environment_transfer_control.c
        src/classes/environment/environment_get_value.c
        src/classes/environment/environment_get_status.c
        src/classes/environment/environment_set_status.c
        )

set(WORD_WORK
        src/classes/word_work/word_work_delete.c
        src/classes/word_work/word_work_expand.c
        src/classes/word_work/word_work_add_char.c
        src/classes/word_work/word_work_ret_word.c
        src/classes/word_work/word_work_add_size.c)

FILE(GLOB LIBFT libs/libft/*/*.c)

add_executable(minishell
        ${READ_LINE_SRCS}
        ${PARSE_COMMANDS}
        ${EXEC_ALL_COMMANDS}
        ${CLEAR_COMMAND_LINE}
        ${ENVIRONMENT}
        ${WORD_WORK}
        ${LIBFT}
        main.c)

add_library(test
        ${READ_LINE_SRCS}
        ${PARSE_COMMANDS}
        ${EXEC_ALL_COMMANDS}
        ${CLEAR_COMMAND_LINE}
        ${ENVIRONMENT}
        ${LIBFT}
        main.c)

add_subdirectory(unit_testing)
