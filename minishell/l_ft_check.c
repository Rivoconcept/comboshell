/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:38:41 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/30 15:09:45 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int check_infile(t_cmd *current, t_params *params)
{
    struct stat	statbuf;
    int i;

    i = 0;
    while (current->cmd[i] != NULL)
    {
        if (ft_strncmp(current->cmd[i], "<", 1) == 0 )
        {
            i++;
            if (stat(current->cmd[i], &statbuf) != 0)
            {
                printf("minishell: %s: No such file or directory\n", current->cmd[i]);
                current->flag_less = 1;
                return (params->last_exit_code = 127);
            }
        }
        i++;
    }
    return (0);
}


int manage_less(t_params *params)
{
    t_cmd *current = params->command;
    while (current != NULL)
    {
        if (params && current && check_infile(current, params))
            return (1);
        current = current->next;
    }
    return (0);
}