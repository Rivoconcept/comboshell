/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:31:53 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/19 16:40:13 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void del_env_element(t_env **myenv, const char *name)
{
    t_env *current;
    t_env *previous;

    if (!myenv || !(*myenv) || !name)
        return;
    current = *myenv;
    previous = NULL;
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
        {
            if (previous == NULL)
                *myenv = current->next;
            else
                previous->next = current->next;

            free(current->name);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

char *ft_getenv(t_params *params, char *name)
{
    t_env   *current;

    if (!params || !name)
        return (NULL);
    current = params->myenvp;
    while (current != NULL)
    {
        if (!ft_strcmp(current->name, name))
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

void print_env(t_params *params)
{
    t_env *current = params->myenvp;

    while (current != NULL)
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

void ft_env(t_params *params)
{
    print_env(params);
}