/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:41:20 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/17 21:41:20 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_here(char* delimiter, char **here_content)
{
    char *line;
    size_t len;
    size_t new_len;

    len = 0;
    *here_content = malloc(1);
    **here_content = '\0';
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            new_len = len + ft_strlen(delimiter) + 1;
            *here_content = ft_realloc(*here_content, new_len + 1);
            ft_strcat(*here_content, delimiter);
            ft_strcat(*here_content, "\n");
            free(line);
            break;
        }
        new_len = len + ft_strlen(line) + 1;
        *here_content = ft_realloc(*here_content, new_len + 1);
        ft_strcat(*here_content, line);
        ft_strcat(*here_content, "\n");
        len = new_len;
        free(line);
    }
}


void process_here(char **input, char **keys)
{
    int i;
    char *here_content;
    size_t new_size;

    i = 0;
    here_content = NULL;
    while (keys[i])
    {
        handle_here(keys[i], &here_content);
        if (here_content)
        {
            free(here_content);
            here_content = NULL;
        }
        i++;
    }
}
