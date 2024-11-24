/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 13:20:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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