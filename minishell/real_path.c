/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:03:42 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 20:03:42 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_absolute_path(const char *path)
{
    if (path[0] == '/')
        return (1);
    return (0);
}

int is_executable_name(const char *path)
{
    if (ft_strchr(path, '/') == NULL)
        return (1);
    return (0);
}

static char **stack_path(const char *path, int *top)
{
    char **stack;
    char **token;
    char *path_copy;
    int i;

    stack = malloc(ft_strlen(path) * sizeof(char*));
    path_copy = ft_strdup(path);
    token = ft_split(path_copy, '/');
    i = 0;
    while (token[i] != NULL) {
        if (ft_strcmp(token[i], "..") == 0) {
            if ((*top) >= 0)
                (*top)--;
            else if (!is_absolute_path(path))
                stack[++(*top)] = token[i];
        } else if (ft_strcmp(token[i], ".") != 0)
            stack[++(*top)] = token[i];
        i++;
    }
    free(path_copy);
    return (stack);
}

char* simplify_path(const char *path)
{
    int top;
    char *simplified_path;
    char **stack;
    int i;

    top = -1;
    simplified_path = malloc(PATH_MAX);
    stack = stack_path(path, &top);
    i = 0;
    if (is_absolute_path(path))
        ft_strcpy(simplified_path, "/");
    else
        simplified_path[0] = '\0';
    while (i <= top)
    {
        ft_strcat(simplified_path, stack[i]);
        if (i < top)
            ft_strcat(simplified_path, "/");
        i++;
    }
    free(stack);
    return (simplified_path);
}
