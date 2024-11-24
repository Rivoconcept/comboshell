/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_list_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:21:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 20:54:21 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_new_cmd(char *input, t_params *params)
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    new_cmd->cmd = put_argv(input, params);
    new_cmd->next = NULL;
    return (new_cmd);
}

t_cmd *create_list_cmd(char **split_cmd, t_params *params)
{
    int i;
    t_cmd *command;
    t_cmd *new_cmd;
    t_cmd *current;

    i = -1;
    command = NULL;
    current = NULL;
    while (split_cmd[++i] != NULL)
    {
        new_cmd = create_new_cmd(split_cmd[i], params);
        if (!new_cmd)
            return (free_list_cmd(command), NULL);
        if (command == NULL)
            command = new_cmd;
        else
        {
            current = command;
            while (current->next != NULL)
                current = current->next;
            current->next = new_cmd;
        }
    }
    return (command);
}

t_cmd *return_commands(char *input, t_params *params)
{
    char    *new_input;
    char    **split_cmd;
    t_cmd   *command;

    command = NULL;
    new_input = format_input(input, "&|<>;");
    if (!new_input)
        return (NULL);
    split_cmd = ft_split(new_input, '|');
    command = create_list_cmd(split_cmd, params);
    if (params->envp)
    {
        free_array(params->envp);
        params->envp = NULL;
    }
    params->envp = put_envp(params);
    if (!params->envp)
        cleanup_and_exit(params, input, 1);
    free(new_input);
    free_array(split_cmd);
    return (command);
}

t_params *create_list_params(char **envp)
{
    int         i;
    t_env       *myenvp;
    t_params    *params;

    i = 0;
    myenvp = NULL;
    params = malloc(sizeof(t_params));
    if (!params)
        return (NULL);
    while (envp[i] != NULL)
    {
        create_env(&myenvp, envp[i]);
        i++;
    }
    params->cmd = NULL;
    params->myenvp = myenvp;
    params->envp = NULL;
    params->var_temp = NULL;
    params->status = 0;
    return (params);
}

