# MINI SHELL

Minishell is a simple shell implementation written in C. It provides basic functionalities similar to a Unix shell.

## Table of Contents

- [Features](#features)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Usage](#usage)

## Features

- Basic shell commands execution
- Built-in commands support
- Input/output redirection
- Environment variable handling
- Signal handling

## How It Works

Minishell operates by continuously reading user input, parsing it, and executing the corresponding commands. Here's a high-level overview of its workflow:

1. **Initialization**: The shell initializes necessary data structures and sets up the environment.
2. **Prompt Display**: The shell displays a prompt to the user, indicating that it is ready to accept commands.
3. **Input Reading**: The shell reads the input from the user.
4. **Parsing**: The input is parsed to identify the command and its arguments. This includes handling special characters for input/output redirection and environment variables.
5. **Execution**: The parsed command is executed. If it is a built-in command, the shell handles it internally. Otherwise, it forks a new process to execute the command using the system's `exec` family of functions.
6. **Signal Handling**: The shell handles signals such as `SIGINT` (Ctrl+C) to ensure proper termination and cleanup.
7. **Loop**: The shell returns to the prompt display step, ready to accept the next command.

## Installation

To install and build Minishell, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/minishell.git
    cd minishell
    ```

2. Build the project using `make`:
    ```sh
    make
    ```

## Usage

To start the shell, run the following command after building the project:
```sh
./minishell
