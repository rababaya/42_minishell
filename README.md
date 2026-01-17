# Minishell

*This project has been created as part of the 42 curriculum by rababaya, dgrigor2*

## Description

Minishell is a simplified implementation of a Unix shell, created as part of the 42 school curriculum. The project aims to recreate the core functionality of a command-line interpreter, allowing users to execute programs, manage processes, and interact with the file system through a command prompt.

### Goal

The goal of this project is to understand how shells work at a fundamental level by implementing essential features including:
- Command parsing and tokenization
- Command execution with pipes and redirections
- Built-in commands (cd, echo, pwd, export, unset, env, exit)
- Environment variable expansion
- Signal handling (SIGINT, SIGQUIT, etc.)
- Heredoc support

### Project Overview

Minishell reads user input, parses it into tokens, identifies redirections and pipes, and executes commands accordingly. It supports both built-in shell commands and external programs, providing a functional command-line interface similar to bash or sh.

## Instructions

### Compilation

To compile the project:

```bash
make
```

This will compile the minishell executable using the provided Makefile, which compiles all source files from the project directories (builtins, execution, expansion, tokenisation, etc.) and links with the custom libft library.

### Installation

No additional installation is required beyond compilation. The project uses standard POSIX libraries and the readline library for enhanced command-line editing.

### Execution

To run the minishell:

```bash
./minishell
```

Once started, you can type commands just like in a regular shell:

```bash
$ ls -la
$ echo "Hello, World!"
$ pwd
$ export MY_VAR=value
$ unset MY_VAR
```

### Cleaning Up

To remove compiled object files:

```bash
make clean
```

To remove all compiled files including the executable:

```bash
make fclean
```

To recompile from scratch:

```bash
make re
```

## Features

- **Command Execution**: Execute external programs and built-in commands
- **Built-in Commands**: 
  - `cd` - Change directory
  - `echo` - Print text
  - `pwd` - Print working directory
  - `export` - Set environment variables
  - `unset` - Unset environment variables
  - `env` - Display environment variables
  - `exit` - Exit the shell
- **Pipes**: Chain commands with `|` to pass output between programs
- **Redirections**: 
  - Input redirection: `<`
  - Output redirection: `>`
  - Append redirection: `>>`
  - Heredoc: `<<`
- **Environment Variable Expansion**: Variables prefixed with `$` are expanded
- **Signal Handling**: Proper handling of SIGINT and other signals
- **History**: Readline integration for command history and editing

## Technical Choices

### Architecture

The project is organized into modular directories:
- **builtins/**: Implementation of built-in shell commands
- **execution/**: Core execution engine, pipes, and redirection logic
- **expansion/**: Variable expansion and conversion utilities
- **tokenisation/**: Lexical analysis and token generation
- **env_operations/**: Environment variable management
- **signals/**: Signal handling implementation
- **utils/**: Utility functions for memory management and string operations

### Key Components

- **Tokenization**: Input is first tokenized into meaningful units (words, operators, redirections)
- **Parsing**: Tokens are analyzed to identify command structure, pipes, and redirections
- **Execution**: Commands are executed using fork/exec for external programs or direct function calls for built-ins
- **Environment Management**: Custom linked-list implementation for efficient environment variable storage and lookup

## Resources

### Documentation and References

- **Bash Manual**: https://www.gnu.org/software/bash/manual/
- **Linux man pages**: `man bash`, `man sh`, `man execve`, `man pipe`

### Tutorials and Articles

- GNU Bash Reference Manual: https://www.gnu.org/software/bash/manual/bash.html
- Linux Programmer's Manual (man 2 for system calls)
- Shell Scripting Guide: https://www.gnu.org/software/bash/manual/bash.html

## AI Usage

AI assistance was used for the following tasks:

- **Debugging and Error Handling**: AI assisted in identifying edge cases and improving error handling throughout the codebase
- **Documentation**: AI helped create clear comments and documentation for complex functions, particularly in the execution and tokenization modules
- **Code Review and Optimization**: AI provided suggestions for code improvements, memory management best practices, and potential refactoring opportunities
- **README and Project Documentation**: AI generated this comprehensive README to help new developers understand the project structure and purpose
