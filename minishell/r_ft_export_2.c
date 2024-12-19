/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:40:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/19 17:42:46 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*create_new_list_export(char *envp)
{
	t_export	*new_exp;
	char		**temp;

	if (!envp)
		return (NULL);
	temp = ft_split(envp, '=');
	if (!temp || !temp[0])
		return (free_array(temp), NULL);
	new_exp = malloc(sizeof(t_export));
	if (!new_exp)
		return (perror("malloc"), free_array(temp), NULL);
	new_exp->name = ft_strdup(temp[0]);
	if (!new_exp->name)
		return (free(new_exp), free_array(temp), NULL);
	if (temp[1])
	{
		new_exp->value = ft_strdup(temp[1]);
		if (!new_exp->value)
			return (free(new_exp->name), free(new_exp), free_array(temp), NULL);
	}
	else if (ft_strchr(envp, '='))
		new_exp->value = ft_strdup("\0");
	else
		new_exp->value = NULL;
	new_exp->next = NULL;
	return (free_array(temp), new_exp);
}

int	create_export(t_export **myexport, char *envp)
{
	t_export	*current;
	t_export	*new_exp;

	if (!myexport || !envp)
		return (0);
	new_exp = create_new_list_export(envp);
	if (!new_exp)
		return (0);
	if (*myexport == NULL)
		*myexport = new_exp;
	else
	{
		current = *myexport;
		while (current->next != NULL)
			current = current->next;
		current->next = new_exp;
	}
	return (1);
}

char	*put_name_export(char *str)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = 0;
	if (!str || !ft_strchr(str, '='))
		return (ft_strdup(str));
	while (str[size] != '\0' && str[size] != '=' && str[size] != '+')
		size++;
	name = (char *)malloc(sizeof(char) * (size + 1));
	if (!name)
		return (NULL);
	while (i < size)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*put_value_export(char *str)
{
	int		i;
	int		j;
	char	*value;

	if (!str || !ft_strchr(str, '='))
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	j = 0;
	while (str[i + 1 + j] != '\0')
		j++;
	value = (char *)malloc(sizeof(char) * (j + 1));
	if (!value)
		return (NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

int	find_export_name(t_export *myexport, char *name)
{
	t_export	*current;

	if (!name)
		return (0);
	current = myexport;
	while (current != NULL)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name)))
			return (1);
		current = current->next;
	}
	return (0);
}

void del_export_element(t_export **myexport, char *envp)
{
    t_export *current;
    t_export *previous;

    if (!myexport || !*myexport || !envp)
        return;

    current = *myexport;
    previous = NULL;

    while (current)
    {
        if (ft_strlen(current->name) == ft_strlen(envp) && 
            ft_strncmp(current->name, envp, ft_strlen(envp)) == 0)
        {
            if (previous == NULL)
                *myexport = current->next;
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

char	*put_export_val(t_export *myexport, char *name)
{
	char		*export;
	char		*temp;
	t_export	*current;

	temp = NULL;
	export = NULL;
	current = myexport;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, name))
		{
			temp = ft_strjoin(name, "=");
			export = ft_strjoin(temp, current->value);
			free(temp);
			return (export);
		}
		current = current->next;
	}
	return (NULL);
}
