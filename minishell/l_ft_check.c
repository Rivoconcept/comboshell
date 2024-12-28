/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:38:41 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/28 10:07:37 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_less(t_params *params)
{
    t_cmd *current = params->command;

    while (current != NULL)
    {
        if (current->flag_less)
            return (1);
        current = current->next;
    }
    return (0);
}

int check_infile(t_cmd *current)
{
    struct stat	statbuf;
    int i;

    i = 0;
    while (current->cmd[i] != NULL)
    {
        if (ft_strcmp(current->cmd[i], "<") == 0 )
        {
            if (stat(current->cmd[++i], &statbuf) != 0)
            {
                current->flag_less = 1;
                return (printf("minishell: %s: No such file or directory\n", current->cmd[i]), 127);
            }
        }
        i++;
    }
    return (0);
}


void manage_less(t_params *params)
{
    t_cmd *current = params->command;
    while (current != NULL)
    {
        check_infile(current);
        current = current->next;
    }
}