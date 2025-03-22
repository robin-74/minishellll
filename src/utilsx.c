#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void intro()
{
    write(1, "\nminishell> ", 12);
}

void skipswhiteSpaces(char **input)
{
    while (**input == ' ')
        (*input)++;
}

void handleEcho(char *input)
{
    int print_nl = 1;

    if (ft_strncmp(input, "echo", 4) == 0)
    {
        input += 4;
        skipswhiteSpaces(&input);
        if (ft_strncmp(input, "-n", 2) == 0)
        {
            print_nl = 0;
            input += 2;
            skipswhiteSpaces(&input);
        }
        ft_printf("%s", input);
        if (print_nl)
            write(1, "\n", 1);
    }
}

ssize_t ftgetline(char **lineptr, size_t *n)
{
    size_t i;
    char buffer[2000];
    ssize_t bytes_read;

    i = 0;
    if (!*lineptr)
    {
        *lineptr = malloc(90000);
        if (!*lineptr)
            return -1;
        *n = 128;
    }
    while (1)
    {
        bytes_read = read(STDIN_FILENO, buffer, 1999);
        if (bytes_read <= 0)
            return -1;
        buffer[bytes_read] = 0;
        i = 0;
        while (i < (size_t)bytes_read)
        {
            (*lineptr)[i] = buffer[i];
            if (buffer[i++] == '\n')
            {
                (*lineptr)[i] = 0;
                handle_input(*lineptr, lineptr);  
                return i;
            }
        }
    }
}

void handle_input(char *input, char **lineptr)
{
    if (!ft_strncmp(input, "exit", 4))
    {
        free(*lineptr);
        write(1, "Exiting minishell...\n", 21);
        exit(0);
    }
    ft_printf("entered : ->  ");
    write(1, input, ft_strlen(input));
    write(1, "\n", 1);
}

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\nminishell> ", 12);
}
