/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:55:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/13 20:18:19 by rhanitra         ###   ########.fr       */
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

int	ft_print_echo(char *input)
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
            write(1, &input[i], 1);
        i++;
    }
	return (count);
}

int run_echo(char **cmd, int flag[2])
{
    int i;

    i = 1;
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
        ft_print_echo(cmd[i]);
        if (cmd[i + 1] != NULL)
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
