/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:27:25 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/13 18:44:22 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_error_var_temp(char *cmd)
{
    int i;
    char **argv;

    i = 0;
    if (!cmd || !ft_strchr(cmd, '=') || ft_isdigit(cmd[0]))
        return (1);
    argv = ft_split(cmd, '=');
    if (!argv)
        return (1);
    while (argv[0][i] && (ft_isalnum(argv[0][i])
        || argv[0][i] == '_'))
        i++;
    if (argv[0][i] != '\0')
    {
        free_array(argv);
        argv = NULL;
        return (1);
    }
    free_array(argv);
    return (0);
}

int put_var_temp(char **cmd, t_params *params)
{
    int i;

    i = 0;
    while (cmd[i] != NULL)
        i++;
    if (i > 1)
        return (0);
    if (check_error_var_temp(cmd[0]))
        return (0);
    if (params->var_temp)
        free(params->var_temp);
    params->var_temp = ft_strdup(cmd[0]);
    if (!params->var_temp)
    {
        perror("Memory allocation failed on params->var_temp\n");
        exit(EXIT_FAILURE);
    }
    return (params->var_temp != NULL);
}

int ft_export(char **cmd, t_params *params)
{
    char    **var_temp;

    var_temp = NULL;
    if (!ft_strcmp(cmd[0], "export"))
    {
        if (!cmd[1])
            ft_env(params);
        else if (params->var_temp && !ft_strchr(cmd[1], '='))
            create_env(&params->myenvp, params->var_temp);
        else if (ft_strchr(cmd[1], '='))
        {
            if (check_error_var_temp(cmd[1]))
            {
                var_temp = ft_split(cmd[1], '=');
                printf("export: not en identifier: %s\n", var_temp[1]);
                free_array(var_temp);
                return (1);
            }
            else
                create_env(&params->myenvp, cmd[1]);
        }
    }
    return (0);
}

