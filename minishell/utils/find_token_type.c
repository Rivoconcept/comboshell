/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:57:35 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 17:26:44 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int check_variable(char *arg)
{
    int i;

    i = 0;
    while (arg[i] != '\0')
    {
        if (arg[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

int token_type(char *arg)
{
    char    *temp;

    temp = format_quotes(arg);
    if (ft_strcmp(temp, "|") == 0 || ft_strcmp(temp, ">") == 0 
        || ft_strcmp(temp, "<") == 0 || ft_strcmp(temp, ">>") == 0 
        || ft_strcmp(temp, "&&") == 0 || ft_strcmp(temp, "||") == 0)
    {
        free(temp);
        return (1);
    }
    if (temp[0] == '-')
    {
        free(temp);
        return (2);
    }
    if (!check_variable(temp))
    {
        free(temp);
        return (3);
    }
    return (free(temp), 0);
}