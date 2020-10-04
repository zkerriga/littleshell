# minishell
💻🔛🙇 A project that aims to create its own terminal.

### Objective of program:
Our program is a command-shell. It has several [builtins functions](#builtins-functions), and it's also able to run any other binary program files that are located on paths from PATH. Our **minishell** is able to handle [redirects](https://www.gnu.org/software/bash/manual/html_node/Redirections.html) and [pipelines](https://www.gnu.org/software/bash/manual/html_node/Pipelines.html) similar to bash. There is also signal processing `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.

### Builtins functions:
* `echo` with option ’-n’
* `cd` with only a relative or absolute path
* `pwd` without any options
* `export` without any options
* `unset` without any options
* `env` without any options and any arguments
* `exit` without any options

### Prepare:
To download a project, use the command with an additional flag (used for connecting all libraries).
```
git clone https://github.com/zkerriga/minishell --recursive
```
Next, you need to compile the project with the `make` command. The Makefile will report the successful build of the project.

### Usage:
To run the program, just write in the terminal:
```
./minishell
```
After that, **minishell** will greet you with the full path to the current directory. Then you can enter any single-line commands with the bash syntax.

### Examples:
![start](https://github.com/zkerriga/minishell/blob/master/gifs/start.gif)
![pipelines](https://github.com/zkerriga/minishell/blob/master/gifs/pipelines.gif)
![redirect](https://github.com/zkerriga/minishell/blob/master/gifs/redirect.gif)
![signals](https://github.com/zkerriga/minishell/blob/master/gifs/signals.gif)

### Issue:
* The internal `cd` command doesn't enter data in the PWD and OLDPWD environment variables.
* Backslash escaping is handled incorrectly. For example, the following case: `echo "\\"`.
