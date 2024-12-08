/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:55:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/08 14:56:29 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_dash_n(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (str[i] == '-')
    {
        i++;
        j = i;
    }
    else if (str[i] != '-')
        return (0);
    while (str[i] != '\0')
    {
        if (str[i] == 'n')
            j++;  
        i++;
    }
    if (i == j)
        return (1);
    return (0);
}

int	ft_print_echo(char *input, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!input)
		return (count);
    while(input[i] != '\0')
    {
        if (input[i] == '\\')
        {
            i++;
            continue ;
        }
        else
        {
            ft_putchar_fd(input[i], fd);
        }
        i++;
    }
	return (count);
}

int run_echo(char **cmd, int flag[2])
{
    int i = 1;

    while (cmd[i] != NULL)
    {   
        if (!check_dash_n(cmd[i]))
            flag[0] = 1;
        if (check_dash_n(cmd[i]) && !flag[0])
        {
            i++;
            flag[1] = 1;
            continue;
        }
        if (strcmp(cmd[i], ">") == 0 || while_check_char(cmd[i][0], "&|<>;"))
            break;
        ft_print_echo(cmd[i], STDOUT_FILENO);
        close(STDOUT_FILENO);
        if (cmd[i + 1] != NULL && !ft_strcmp(cmd[i + 1], ">")
            && !while_check_char(cmd[i + 1][0], "&|<>;"))
            write(1, " ", 1);
        i++;
    }
    if (!flag[1])
        write(1, "\n", 1);
    return (0);
}

int ft_echo(char **cmd)
{
    int flag[2] = {0, 0};
   
    run_echo(cmd, flag);
    return (0);
}
