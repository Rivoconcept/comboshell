/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:40:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 12:40:16 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *put_env_name(char *envp)
{
    int i = 0;
    int size = 0;
    char *name;

    if (!envp)
        return (NULL);
    while (envp[size] != '=' && envp[size] != '\0')
        size++;
    name = (char *)malloc(sizeof(char) * (size + 1));
    if (!name)
        return (NULL);
    while (i < size)
    {
        name[i] = envp[i];
        i++;
    }
    name[i] = '\0';
    return (name);
}

char *put_env_value(char *envp)
{
    int i = 0;
    int size = 0;
    char *value;

    while (envp[size] != '=' && envp[size] != '\0')
        size++;
    value = (char *)malloc(sizeof(char) * ((ft_strlen(envp) - size) + 1));
    if (!value)
        return (NULL);
    size++;
    while (envp[size] != '\0')
    {
        value[i] = envp[size];
        i++;
        size++;
    }
    value[i] = '\0';
    return (value);
}

void create_env(t_env **myenvp, char *envp)
{
    t_env *current;
    t_env *new_env;

    new_env = malloc(sizeof(t_env));
    if (!new_env)
        return;
    new_env->name = put_env_name(envp);
    new_env->value = put_env_value(envp);
    if (!new_env->name || !new_env->value)
    {
        free(new_env->name);
        free(new_env->value);
        free(new_env);
        return;
    }
    new_env->next = NULL;

    if (*myenvp == NULL)
        *myenvp = new_env;
    else
    {
        current = *myenvp;
        while (current->next != NULL)
            current = current->next;
        current->next = new_env;
    }
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
