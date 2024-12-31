/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:38:41 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/30 19:08:23 by rhanitra         ###   ########.fr       */
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

int isoperators(char *cmd)
{
    int     i;

    i = 0;
    while (cmd[i] != '\0' && is_operator(cmd[i]))
        i++;
    if (cmd[i] == '\0')
        return (1);
    return (0);
}

int check_errors_file_1(char **cmd, int i, t_cmd *current)
{
    if (strcmp(cmd[i], "|") == 0 && (current->previous == NULL || current->previous->cmd == NULL))
    {
        return (printf("minishell: syntax error near unexpected token `|'\n") + 1);
    }
    return (0);
}

int check_errors_file_2(t_cmd *current, int i)
{
    struct stat	statbuf;
    
    if (isoperators(current->cmd[i]) && (ft_strlen(current->cmd[i]) > 2
        || current->cmd[i][1] == '|'))
        return (printf("minishell: syntax error near unexpected token\n") + 1);
    if (isoperators(current->cmd[i]) && strncmp(current->cmd[i], "|", ft_strlen(current->cmd[i])))
    {
        i++;
        if ((current->cmd[i] ==  NULL || isoperators(current->cmd[i]))
            && strncmp(current->cmd[i], "|", ft_strlen(current->cmd[i])))
            return (printf("minishell: syntax error near unexpected token\n") + 1);
        if ((current->cmd[i] && current->cmd[i + 1] && isoperators(current->cmd[i + 1])
            &&  current->cmd[i + 2] ==  NULL)
            && strncmp(current->cmd[i], "|", ft_strlen(current->cmd[i])))
            return (printf("minishell: syntax error near unexpected token\n") + 1);
        if (stat(current->cmd[i], &statbuf) != 0)
        {
            current->flag_less = 1;
            return (printf("minishell: %s: No such file or directory\n", current->cmd[i]) + 126);
        }
    }
    return (0);
}

int check_in_and_outfile(t_cmd *current, t_params *params)
{
    int i;

    i = 0;
    while (current->cmd[i] != NULL)
    {
        params->last_exit_code = check_errors_file_1(current->cmd, i, current);
        if (params->last_exit_code != 0)
            return (params->last_exit_code);
        /*params->last_exit_code = check_errors_file_2(current->cmd[i], i);
        if (params->last_exit_code != 0)
            return (params->last_exit_code);*/

        i++;
    }
    return (0);
}

int manage_less(t_params *params)
{
    t_cmd *current = params->command;
    while (current != NULL)
    {
        if (params && current && check_in_and_outfile(current, params))
            return (1);
        current = current->next;
    }
    return (0);
}