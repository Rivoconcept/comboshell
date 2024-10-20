#include "test.h"

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Pour write() et sleep()

int put_val_env(char *str, int *index, int fd)
{
    int i;
    char var_env[256];
    char *env_value;
    t_params    *params;
    
    i = 0;
    (*index)++;

    while (str[*index] != '\0' && str[*index] != '"' && str[*index] != '\''
        && str[*index] != ' ' && str[*index] != '$')
    {
        var_env[i] = str[*index];
        (*index)++;
        i++;
    }
    (*index)--;
    var_env[i] = '\0';
    env_value = getenv(var_env);
    if (env_value)
        return (ft_putstrfd(env_value, fd));
    else
         return (0);
}

void print_var_env(char *input, int *i, int fd)
{
    if (in_double_quote(input))
        put_val_env(input, i, fd);
    else if (in_single_quote(input))
    {
        if (input[*i - 1] == '\'' && *i > 1)
            put_val_env(input, i, fd);
        else
            ft_putcharfd(input[*i], fd);
    }
    else if (pure_quote(input))
        put_val_env(input, i, fd);
    else if (!pure_quote(input) && !pure_apostrophe(input)
        && !in_double_quote(input) && !in_single_quote(input))
        put_val_env(input, i, fd);
}