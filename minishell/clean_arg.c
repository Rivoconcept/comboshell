/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:36:02 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 14:36:03 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *join_argv(char **argv)
{
    int i;
    char *new_str;
    char *temp = NULL;

    i = 1;
    new_str = ft_strdup(argv[0]);
    if (!new_str)
        return (NULL);
    while (argv[i] != NULL)
    {
        temp = ft_strjoin(new_str, " ");
        free(new_str);
        new_str = temp;
        temp = ft_strjoin(new_str, argv[i]);
        free(new_str);
        new_str = temp;
        i++;
    }
    return (new_str);
}