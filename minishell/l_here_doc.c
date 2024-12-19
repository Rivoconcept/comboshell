/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:41:20 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/18 09:27:55 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void write_here(char* content, int num_cmd) {
    char *file;
    int fd;
    
    file = ft_strjoin("/tmp/josia", ft_itoa(num_cmd));
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1) {
        write(fd, content, ft_strlen(content));
        close(fd);
    }
    free(file);
}

static void handle_here(char* delimiter, char **here_content, int j)
{
    char *line;
    size_t len;
    size_t new_len;
    char *temp;

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
            write_here(*here_content, j);
            free(line);
            break;
        }
        new_len = len + ft_strlen(line) + 1;
        temp = ft_realloc(*here_content, new_len + 1);
        if (!temp)
        {
            free(*here_content);
            free(line);
            return;
        }
        *here_content = temp;
        ft_strcat(*here_content, line);
        ft_strcat(*here_content, "\n");
        len = new_len;
        free(line);
    }
}

void process_here(char **input, char **keys, int j)
{
    int i;
    char *here_content;

    i = 0;
    here_content = NULL;
    (void)input;
    while (keys[i])
    {
        handle_here(keys[i], &here_content, j);
        
        if (here_content)
        {
            free(here_content);
            here_content = NULL;
        }
        i++;
    }
    ft_free(keys, count_array(keys));
}
