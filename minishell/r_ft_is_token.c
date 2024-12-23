/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_is_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:57:35 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 11:23:08 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int token_type(char *arg)
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
}*/