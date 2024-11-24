/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:55:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 12:49:35 by rhanitra         ###   ########.fr       */
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

int run_echo(char **cmd, int flag[2], int fd)
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
        ft_print_echo(cmd[i], fd);
        if (cmd[i + 1] != NULL && !ft_strcmp(cmd[i + 1], ">")
            && !while_check_char(cmd[i + 1][0], "&|<>;"))
            write(fd, " ", 1);
        i++;
    }
    if (!flag[1])
        write(fd, "\n", 1);
    return (0);
}

int ft_echo(char **cmd)
{
    int flag[2] = {0, 0};
    int fd;
    int i;

    i = 0;
    fd = STDOUT_FILENO;
    while (cmd[i] != NULL)
    {
        if (strcmp(cmd[i], ">") == 0)
        {
            if (cmd[i + 1] == NULL)
            {
                perror("Error : unspecified file after '>'");
                return (1);
            }
            fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("Error opening file");
                return (1);
            }
            break;
        }
        i++;
    }
    run_echo(cmd, flag, fd);
    if (fd != STDOUT_FILENO)
        close(fd);
    return (0);
}
