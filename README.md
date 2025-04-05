<p align="center">
	<img src=".badge/minishelle.png"/>
</p> 

<h1 align="center">
	MiniShell
</h1> 

## what is it?
ur own tiny bash-like shell written in C.  
lets u run commands, handle pipes & redirections, and use builtin funcs.

## features
- builtins: `cd`, `echo`, `env`, `exit`, `pwd`, `export`, `unset`  
- support for pipes `|`
- support for redirections `<`, `>`, `>>`
- handle signals: `CTRL-C`, `CTRL-D`
- minimal error handling

## project structure
```
.
├── includes
│   ├── libft
│   │   ├── ft_isalnum.c
│   │   ├── ft_split.c
│   │   ├── ft_strchr.c
│   │   ├── ft_strdup.c
│   │   ├── ft_strjoin.c
│   │   ├── ft_strlcat.c
│   │   ├── ft_strlcpy.c
│   │   ├── ft_strlen.c
│   │   ├── ft_strncmp.c
│   │   ├── libft.h
│   │   └── Makefile
│   └── minishell.h
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── built_in
    │   ├── ft_cd.c
    │   ├── ft_echo.c
    │   ├── ft_env.c
    │   ├── ft_exit.c
    │   ├── ft_export.c
    │   ├── ft_pwd.c
    │   └── ft_unset.c
    ├── exec
    │   └── exec.c
    ├── main.c
    ├── parse
    │   └── readline.c
    └── utils
        ├── error.c
        └── signals.c
```

## how to compile
```
make
```

## how to run
```
./minishell
```

## how to test
- builtin cmds: `cd`, `echo hello`, `pwd`  
- pipes: `ls -l | grep minishell`  
- redirs: `echo hi > out.txt` / `cat < out.txt`

## clean up
```
make fclean
```
