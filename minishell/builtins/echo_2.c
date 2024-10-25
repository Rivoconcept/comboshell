/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:55:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/20 11:23:33 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int put_val_env(char *str, int *index, int fd)
{
    int i;
    char var_env[256];
    char *env_value;
    t_wstatus *status = {0};
    
    i = 0;
    status->value = 0;
    (*index)++;
    if (str[*index] == '?')
    {
        ft_putnbr_fd(status->value, fd);
    }
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

void print_char(char *input, int *i, int fd)
{
    if (in_single_quote(input) && input[*i] != '\'')
        ft_putcharfd(input[*i], fd);
    else if (in_double_quote(input) && input[*i] != '"')
        ft_putcharfd(input[*i], fd);
    else if (pure_apostrophe(input) && input[*i] != '\'')
        ft_putcharfd(input[*i], fd);
    else if (!pure_apostrophe(input) && !pure_quote(input) 
        && !in_double_quote(input) && !in_single_quote(input))
        ft_putcharfd(input[*i], fd);
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
        if (input[i] == '$' && input[i + 1] != '\0' && !pure_apostrophe(input))
        {
            print_var_env(input, &i, fd);
        }
        else
        {
            print_char(input, &i, fd);
        }
        i++;
    }
	return (count);
}


