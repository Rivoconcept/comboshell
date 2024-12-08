/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:57:46 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/25 10:30:14 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int cmd_not_found(t_params *params, char *input)
{
    t_cmd   *current;

    current = params->cmd;
    if (!current->cmd || !current->cmd[0])
        return (0);
    while (current != NULL)
    {
         if (access(current->cmd[0], X_OK | F_OK) != 0)
         {
            free(input);
            free_list_cmd(params->cmd);
            return (1);
         }
         current = current->next;
    }
    return (0);
}

int run_builtins(char **cmd, t_params *params, char *input)
{
    if (!cmd || !cmd[0])
        return (0);
    if (!ft_strcmp(cmd[0], "cd"))
        return (ft_cd(cmd[1], params), 1);
    if (!ft_strcmp(cmd[0], "pwd"))
        return (ft_pwd(), 1);
    if (!ft_strcmp(cmd[0], "env"))
        return (ft_env(params), 1);
    if (!ft_strcmp(cmd[0], "echo"))
        return (ft_echo(cmd), 1);
    if (!ft_strcmp(cmd[0], "unset"))
        del_env_element(&params->myenvp, cmd[1]);
    if (!ft_strcmp(cmd[0], "export"))
        return (ft_export(cmd, params), 1);
    if (!ft_strcmp(cmd[0], "exit"))
        cleanup_and_exit(params, input, 1);
    return (0);
}
