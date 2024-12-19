#include "minishell.h"

void print_argv(char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        // ft_putstr_fd(argv[i], 2);
        // ft_putstr_fd("\n", 2);
        i++;
    }

}


void print_cmd(t_params *params)
{
    t_cmd *current = params->command;

    while (current != NULL)
    {
        print_argv(current->cmd);
        current = current->next;
    }
}
