/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:57:46 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 15:43:46 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_not_found(t_params *params)
{
    t_cmd   *current;

    current = params->command;
    if (!current->cmd || !current->cmd[0])
        return (0);
    while (current != NULL && !isbuiltins(current->cmd[0]))
    {
         if (access(current->cmd[0], X_OK | F_OK) != 0)
            return (1);
         current = current->next;
    }
    return (0);
}

int run_builtins(char **cmd, t_params *params)
{
    if (!cmd || !cmd[0])
        return (0);
    if (!ft_strcmp(cmd[0], "cd"))
        return (ft_cd(cmd[1], params));
    if (!ft_strcmp(cmd[0], "pwd"))
        return (ft_pwd());
    if (!ft_strcmp(cmd[0], "env"))
        return (ft_env(params));
    if (!ft_strcmp(cmd[0], "echo"))
        return (ft_echo(cmd));
    if (!ft_strcmp(cmd[0], "unset"))
        ft_unset(cmd, params);
    if (!ft_strcmp(cmd[0], "export"))
        return (ft_export(cmd, params));
    if (!ft_strcmp(cmd[0], "exit"))
        ft_exit(cmd, params);
    return (0);
}
