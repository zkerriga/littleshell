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
        src/parse_commands/parse_and_go_next.c
        src/parse_commands/destroy_command.c
        src/parse_commands/separate_commands.c
        src/parse_commands/parse_single_command.c
        src/parse_commands/shell_word_split_with_env.c
        src/parse_commands/pre_parse.c
        src/parse_commands/full_cycle_is_redirect.c
        src/parse_commands/full_cycle_blocks.c
        src/parse_commands/parse_redirects.c
        )

set(EXEC_ALL_COMMANDS
        src/exec_all_commands/exec_one_command.c
        src/exec_all_commands/search_path_command.c
        src/exec_all_commands/execution.c
        src/exec_all_commands/parse_stop_status.c
        src/exec_all_commands/open_and_check_redirects.c
        )

set(ERROR_MANAGER
        src/errors/error_manager.c
        )

set(ENVIRONMENT
        src/classes/environment/environment_new.c
        src/classes/environment/environment_del.c
        src/classes/environment/environment_add.c
        src/classes/environment/environment_print.c
        src/classes/environment/environment_print_sorted.c
        src/classes/environment/environment_remove.c
        src/classes/environment/environment_transfer_control.c
        src/classes/environment/environment_get_value.c
        src/classes/environment/environment_get_status.c
        src/classes/environment/environment_set_status.c
        )

set(WORD_WORK
        src/classes/word_work/word_work_new.c
        src/classes/word_work/word_work_delete.c
        src/classes/word_work/word_work_expand.c
        src/classes/word_work/word_work_add_char.c
        src/classes/word_work/word_work_ret_word.c
        src/classes/word_work/word_work_add_size.c)

set(BUILTINS
        src/builtin_functions/env.c
        src/builtin_functions/unset.c
        src/builtin_functions/write_err.c
        src/builtin_functions/export.c
        src/builtin_functions/exit.c
        src/builtin_functions/echo.c
        src/builtin_functions/cd.c
        src/builtin_functions/pwd.c
        )

FILE(GLOB LIBFT libs/libft/*/*.c)

add_executable(minishell
        ${ERROR_MANAGER}
        ${BUILTINS}
        ${READ_LINE_SRCS}
        ${PARSE_COMMANDS}
        ${EXEC_ALL_COMMANDS}
        ${ENVIRONMENT}
        ${WORD_WORK}
        ${LIBFT}
        main.c src/signal_handlers/handlers.c)

add_library(test
        ${ERROR_MANAGER}
        ${BUILTINS}
        ${READ_LINE_SRCS}
        ${PARSE_COMMANDS}
        ${EXEC_ALL_COMMANDS}
        ${ENVIRONMENT}
        ${WORD_WORK}
        ${LIBFT}
        main.c)

add_subdirectory(unit_testing)
