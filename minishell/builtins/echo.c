/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:55:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/25 11:46:35 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"


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
            ft_putcharfd(input[i], fd);
        }
        i++;
    }
	return (count);
}

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

    i = 0;
    (void)argc;
    fd = STDOUT_FILENO;
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
