/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:25:12 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/16 15:39:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("minishell: %s$ ", cwd);
    } else {
        perror("getcwd() error");
    }
}

int ft_is_space(char c)
{
    return ((c >= '\t' && c <= '\r') || c == 32);
}

int while_check_char(char c, char *input)
{
    int     i;

    i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int find_first_index(const char *big, const char *little)
{
    size_t i;
    size_t j;
    size_t len;

    i = 0;
    j = 0;
    len = ft_strlen((char *)little);
    if (!*little)
        return (0);
    while (big[i] != '\0' && len > 0)
    {
        j = 0;
        if (big[i] == little[j] && i != 0)
        {
            while (little[j] && j < len && big[i + j] == little[j])
                j++;
            if (little[j] == '\0')
                return (i);
        }
        i++;
    }
    return (0);
}

void free_array(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i] != NULL)
    {
        if (arr[i])
            free(arr[i]);
        i++;
    }
    if (arr)
        free(arr);
}

