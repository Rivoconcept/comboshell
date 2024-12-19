/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_list_env_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:40:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/16 14:56:14 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *create_new_list_env(char *envp)
{
    t_env *new_env = NULL;
    char **temp = NULL;

    if (!envp)
        return (NULL);
    temp = ft_split(envp, '=');
    if (!temp || !temp[0] || !temp[1])
        return (NULL);

    new_env = malloc(sizeof(t_env));
    if (!new_env)
        return (perror("malloc"), free_array(temp), NULL);
    new_env->name = ft_strdup(temp[0]);
    new_env->value = ft_strdup(temp[1]);
    if (!new_env->name || !new_env->value)
        return (free_list_env(new_env), free_array(temp), NULL);
    new_env->next = NULL;
    free_array(temp);
    return (new_env);
}


int create_env(t_env **myenvp, char *envp)
{
    t_env *current;
    t_env *new_env;

    new_env = create_new_list_env(envp);
    if (!new_env)
        return (0);
    if (*myenvp == NULL)
        *myenvp = new_env;
    else
    {
        current = *myenvp;
        while (current->next != NULL)
            current = current->next;
        current->next = new_env;
    }
    return (1);
}

char *put_env_val(t_env *myenv, char *name)
{
    t_env *current;

    current = myenv;
    while (current != NULL)
    {
        if (!ft_strcmp(current->name, name))
            return (current->value);
        current = current->next;
    }
    return (NULL);
}
