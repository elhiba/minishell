#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <readline/readline.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef PRINT_DEBUG_H
# define PRINT_DEBUG_H
# define p_d(d)     printf(#d " = %d\n", d)
# define p_ld(ld)   printf(#ld " = %ld\n", ld)
# define p_s(s)     printf(#s " = %s\n", s)
# define p_p(p)     printf(#p " = %p\n", p)
# define p_x(x)     printf(#x " = %x\n", x)
#endif

#define PIPE_BUFFER_SIZE 65536

int    main(int argc, char **argv)
{
    int fds[2];

    if (argc < 2)
    {
        dprintf(2, "Usage: %s <urShell>\n", argv[0]);
        return 1;
    }

    pipe(fds);

    dup2(fds[1], 1);
    int i = 0;
    while (i < PIPE_BUFFER_SIZE)
    {
        write(1, "x", 1);
        i++;
    }
    execvp(argv[1], argv + 1);
    perror("debug");
}
