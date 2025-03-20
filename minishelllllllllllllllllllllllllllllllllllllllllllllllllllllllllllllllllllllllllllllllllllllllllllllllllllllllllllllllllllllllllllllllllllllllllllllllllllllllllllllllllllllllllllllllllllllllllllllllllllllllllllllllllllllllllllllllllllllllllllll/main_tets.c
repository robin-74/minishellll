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
    {
        (*input)++;
    };
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
                print_newline = 0;
                input += 2;
                skipswhiteSpaces(&input);
            };
            ft_printf("%s",input);
            if (print_newline)
            {
                write(1, "\n". 1);
            }
        }
}
void handleEcho(char *input)
{
    int print_newline = 1;  // Flag to decide if we should print a newline or not.

    // Skip "echo" and leading spaces
    if (ft_strncmp(input, "echo", 4) == 0)
    {
        input += 4;
        skipswhiteSpaces(&input);

        // Check for the -n flag
        if (ft_strncmp(input, "-n", 2) == 0)
        {
            print_newline = 0;  // Set flag to false if -n is found
            input += 2;
            skipswhiteSpaces(&input);  // Skip any spaces after -n
        }

        // Now, print the rest of the input
        write(1, input, ft_strlen(input));

        // Print newline if the flag is set
        if (print_newline)
        {
            write(1, "\n", 1);
        }
    }
}

ssize_t ftgetline(char **lineptr, size_t *n)
{
    size_t position;
    char buffer[2000];
    ssize_t bytes_read;
    ssize_t i;

    position = 0;
    if (!*lineptr)
    {
        if (!(*lineptr = malloc(90000)))
            return -(1);
        *n = 128;
    }
    while (1)
    {
        bytes_read = read(STDIN_FILENO, buffer, 1999);
        if (bytes_read <= 0)
            return (-1); // handle case ctrl D 0 return 0
        buffer[bytes_read] = 0;
        i = 0;
        while (i < bytes_read)
        {
            (*lineptr)[position] = buffer[i];
            if (buffer[i++] == '\n')
                return ((*lineptr)[position + 1] = 0) + position + 1;
            position++;
        }
    }
}

void handle_input(char *input)
{
    if (!ft_strncmp(input, "exit", 4) || !ft_strncmp(input, "a", 1))
    {
        free(input);
        exit(0);
    }
    handleEcho(input);
    ft_printf("entered : ->  ");
    write(1, input, ft_strlen(input));
    write(1, "\n", 1);
}

void sigint_handler(int sig)
{
    (void)sig;
    write(1,"handle sig", 10);
    write(1, "\nminishell> ", 12);
}

int main(void)
{
    char *input;
    size_t len;
    ssize_t nr;

    input = NULL;
    len = 0;
    signal(SIGINT, sigint_handler);

    while ((nr = ftgetline(&input, &len)) > -1)
    {
        intro();
        if (nr > 0 && input[nr - 1] == '\n')
            input[nr - 1] = 0;
        if (nr > 0)
            handle_input(input);
        free(input);
        input = NULL;
    }
    free(input);
    return (0);
}
