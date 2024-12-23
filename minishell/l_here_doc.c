/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:41:20 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/23 15:01:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int process_quotes(char **key)
{
    int quote = 0;
    char *temp;

    if (ft_memchr(*key, '"', ft_strlen(*key) + 1) || ft_memchr(*key, '\'', ft_strlen(*key) + 1))
        quote = 1;

    if (ft_strcmp(*key, "\"\"") != 0 || ft_strcmp(*key, "''") != 0)
{
        temp = format_quotes(*key);
        free(*key);
        *key = ft_strdup(temp);
        free(temp);
    }

    return quote;
}

void process_here(char **keys, int j, t_params *params)
{
    int i = 0;
    char *here_content = NULL;
    int quote;

    while (keys[i])
{
        quote = process_quotes(&keys[i]);
        handle_here(keys[i], &here_content, j, quote, params);

        if (here_content)
{
            free(here_content);
            here_content = NULL;
        }
        i++;
    }
}


/*
void process_here(char **keys, int j, t_params *params)
{
    int i;
    char *here_content;
    int quote;
    char *temp;

    i = 0;
    quote = 0;
    here_content = NULL;
    while (keys[i])
    {
        if (ft_memchr(keys[i], '"', ft_strlen(keys[i]) + 1)
            || ft_memchr(keys[i], '\'', ft_strlen(keys[i]) + 1) )
            quote = 1;
        if (ft_strcmp(keys[i], "\"\"") != 0 || ft_strcmp(keys[i], "''") != 0)
        {
            temp = format_quotes(keys[i]);
            free(keys[i]);
            keys[i] = ft_strdup(temp);
            free(temp);
        }
        handle_here(keys[i], &here_content, j, quote, params);
        if (here_content)
        {
            free(here_content);
            here_content = NULL;
        }
        i++;
    }
}
*/