/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:19:02 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 15:54:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *multiline(char **input)
{
    char *line;
    size_t len = 0;

    top:
    if ((*input)[ft_strlen(*input) - 1] == '\\')
        *input = ft_substrj(*input, 0, ft_strlen(*input) - 1);
    else
    {
        *input = ft_realloc(*input, sizeof(char) * (ft_strlen(*input) + 2));
        strcat(*input, "\n");
    }
    line = readline("> ");
    if(*line)
    {
        len = ft_strlen(line) + 1;
        *input = ft_realloc(*input, sizeof(char) * (ft_strlen(*input) + len));
        ft_strcat(*input, line);
        if (check_quote(*input) == 1 || line[ft_strlen(line) - 1] == '\\')
        {
            free(line);
            goto top;
        }
        free(line);
    }
    return *input;
}