/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 20:55:40 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_var_env(t_env *myenv, char **envp)
{
    int i = 0;
    while (envp[i] != NULL)
    {
        create_env(&myenv, envp[i]);
        i++;
    }
}

int count_list_env(t_params *params)
{
    int     i;
    t_env    *current;

    i = 0;
    current = params->myenvp;
    while(current != NULL)
    {
        i++;
        current = current->next;
    }
    return (i);
}

char **put_envp(t_params *params)
{	
    int i;
    t_env *current;
    char **myenvp;
    char *temp;

    i = 0;
    myenvp = (char **)malloc(sizeof(char *) * (count_list_env(params) + 1));
    if (!myenvp)
        return (NULL);
    current = params->myenvp;
    while (current != NULL)
    {
        temp = ft_strjoin(current->name, "=");
        if (!temp)
            return (free_array(myenvp), NULL);
        myenvp[i] = ft_strjoin(temp, current->value);
        free(temp);
        if (!myenvp[i])
            return (free_array(myenvp), NULL);
        current = current->next;
        i++;
    }
    myenvp[i] = NULL;
    return (myenvp);
}

void put_val_exit_status(t_params *params)
{
    int sig;
    char *ws_val;
    char *temp;

    sig = 0;
    ws_val = NULL;
    temp = NULL;
    if (WIFSIGNALED(params->status))
    {
        sig = WTERMSIG(params->status);
        if (sig == SIGINT)
            ws_val = ft_itoa(128 + sig);
        else
            ws_val = ft_itoa(128 + sig);
    }
    else if (WIFEXITED(params->status))
        ws_val = ft_itoa(WEXITSTATUS(params->status));
    else
        printf("Error: Child process did not terminate properly.\n");
    if (ws_val)
    {
        temp = ft_strjoin("?=", ws_val);
        free(ws_val);
        create_env(&params->myenvp, temp);
        free(temp);
    }
    else
        printf("Error: ws_val is NULL\n");
}