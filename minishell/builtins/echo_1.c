/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:55:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/19 21:25:11 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_echo(char **argv, int flag[2], int fd)
{
    int i = 1;

    while (argv[i] != NULL)
    {   
        if (!check_dash_n(argv[i]))
            flag[0] = 1;
        if (check_dash_n(argv[i]) && !flag[0])
        {
            i++;
            flag[1] = 1;
            continue;
        }
        if (strcmp(argv[i], ">") == 0 || while_check_char(argv[i][0], "&|<>;"))
            break;
        ft_print_echo(argv[i], fd);
        if (argv[i + 1] != NULL && strcmp(argv[i + 1], ">") != 0 
            && !while_check_char(argv[i + 1][0], "&|<>;"))
            write(fd, " ", 1);
        i++;
    }
    if (!flag[1])
        write(fd, "\n", 1);
    return (0);
}

int main(int argc, char **argv)
{
    int flag[2] = {0, 0};
    int fd;
    int i;
   // t_wstatus *status = {0};

    i = 0;
    (void)argc;
    fd = STDOUT_FILENO;
    //printf("%d\n", status->value);
    while (argv[i] != NULL)
    {
        if (strcmp(argv[i], ">") == 0)
        {
            if (argv[i + 1] == NULL)
            {
                perror("Error : unspecified file after '>'");
                return (1);
            }
            fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("Error opening file");
                return (1);
            }
            break;
        }
        i++;
    }
    ft_echo(argv, flag, fd);
    if (fd != STDOUT_FILENO)
        close(fd);
    return (0);
}

/*int ft_echo(char **argv, int , int flag[2])
{
    int i;

    i = 1;
    while (argv[i] != NULL)
    {   
        if (!check_dash_n(argv[i]))
            flag[0] = 1;
        if (check_dash_n(argv[i]) && !flag[0])
        {
            i++;
           flag[1] = 1;
            continue;
        }
        if (while_check_char(argv[i][0], "&|<>;"))
            break ;
        ft_print_str_in_quotes(argv[i]);
        if (argv[i + 1] != NULL && !while_check_char(argv[i + 1][0], "&|<>;"))
            printf(" ");
        i++;
    }
    if (!flag[1])
        printf("\n");
    return ();
}

int	main(int argc, char **argv)
{
    int count;
    int flag[2];

    count = 0;
    flag[0] = 0;
    flag[1] = 0; 
	(void)argc;

    return (ft_echo(argv, &count, flag));
}*/