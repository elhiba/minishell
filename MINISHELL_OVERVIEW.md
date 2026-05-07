# Minishell Architecture Overview

## Code structure

- `includes/`
  - `minishell.h`: public types, flags, and function prototypes used across the project.
  - `libft/`: 42 libft helpers.
  - `gcft/`: the `ft_collector` allocator used as a lightweight GC for tracked allocations.
- `src/main.c`: entry point and REPL loop.
- `src/parse/`: syntax checks, tokenization/lexing, expansions, and command list building.
  - `syntax/`: operator/quote validation.
  - `spliter/`: token splitting and operator/quote detection.
  - `dollar_expand/`: `$VAR`/`$?` expansion logic.
  - `split_expander/`: splits expanded tokens on spaces when allowed.
  - `set_cmd_list/`: builds `t_cmd` nodes (argv, redirs, heredocs).
  - `heredoc/`: here-document collection and expansion.
  - `prompt/`: dynamic prompt formatting (git branch, exit status).
- `src/exec/`: redirection checks, error handling, and execution (single command vs pipelines).
- `src/built_in/`: builtin command implementations (`cd`, `echo`, `env`, `exit`, `pwd`, `export`, `unset`).
- `src/utils/`: signals, error helpers, linked list helpers, environment utilities.

## Core data structures

- `t_data`: global session state (input line, environment, token list, last exit code, saved stdio).
- `t_token`: doubly linked list node for lexical tokens with flags (quotes, redirections, env var, etc.).
- `t_cmd`: execution node for a single pipeline segment (cmd path, argv, heredocs, redir fds/paths).
- `t_heredoc`: linked list describing heredoc delimiter, temp file, and expansion behavior.

## High-level control flow

1. `main()` initializes `t_data`, installs signal handlers, and loops forever.
2. Each loop builds the prompt, reads input via `readline()`, and stores history.
3. `ft_parse()` performs syntax checking, tokenization, command building, heredoc handling,
   error checks, and finally execution.
4. The line is freed and the loop continues.

## Lexing / tokenization steps

1. **Syntax validation** (`syntax_checker`):
   - Validates operators (`|`, `<`, `>`, `<<`, `>>`) and unmatched quotes before parsing.
2. **Pipe split** (`ft_tokenizer` → `special_split`):
   - Splits the line into pipeline segments by `|`, respecting quotes.
3. **Token split per segment** (`ft_spliter`):
   - Scans each segment and creates `t_token` nodes for operators, quoted strings, and words.
   - Marks whether a token was quoted and whether a space followed it.
4. **Expansion** (`check_and_expand`):
   - Expands `$VAR` and `$?` unless inside single quotes or heredoc delimiters.
   - Tracks non-splittable expansions when `$` does not introduce a variable name.
5. **Split expanded values** (`split_expanded`):
   - If an expanded token contains spaces and is not quoted, it is split into multiple tokens.
6. **Join tokens** (`join_tokens`):
   - Re-joins tokens that were originally contiguous (no space between them).
7. **Redirection typing** (`typer`):
   - Marks the token following `<`, `>`, `<<`, `>>` as infile/outfile/heredoc/append.
8. **Ambiguous redirect marking** (`set_ambiguous`):
   - Detects redirections that expand into multiple words or empty values.

## Parsing / command list building

1. `exec_setup()` iterates each pipeline segment and calls `cmd_builder()`.
2. `cmd_builder()` creates a `t_cmd` node and:
   - Sets the command name (resolves `PATH` for non-builtin commands).
   - Builds `argv` from remaining word tokens.
   - Collects heredoc descriptors.
3. The result is a linked list of `t_cmd`, one per pipeline segment.

## Execution flow

1. **Heredoc collection** (`heredoc()`):
   - For each command’s heredoc list, forks a reader that accepts lines until the delimiter.
   - Expands variables in heredoc content unless the delimiter was quoted.
2. **Redirection & command errors** (`check_errors()`):
   - Validates redirection targets (missing file, directory, ambiguous expansion).
   - Sets `stdin`/`stdout` file paths for later use.
   - Reports command-not-found and permission errors.
3. **Execute** (`execute()`):
   - If one command, `single_command()` runs builtins in-process or forks/execs external cmds.
   - If multiple commands, `multiple_pipes()` forks each command, wires pipes, and waits.
4. **Exit status** (`save_exit_status()`):
   - Captures exit code or signal-based status and stores it in `t_data.last_exit_code`.

## General minishell algorithm (summary)

1. Initialize state and install interactive signal handlers.
2. Display prompt and read a line.
3. Reject invalid syntax (unclosed quotes or malformed operators).
4. Split input into pipeline segments and tokenize each segment.
5. Expand variables and split/join tokens based on quoting and spacing rules.
6. Build a command list with argv, redirections, and heredocs.
7. Resolve heredocs and prepare redirection targets.
8. Execute builtins directly or fork/exec external commands (with pipes when needed).
9. Store exit status, clean up, and repeat.
