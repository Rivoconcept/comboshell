/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:19:41 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/03 11:20:54 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int first_check_var_export(char *cmd)
{
	char	*temp;

	temp = NULL;
	if (!cmd || cmd[0] == '\0' || cmd[0] == '+' \
		|| cmd == NULL || ft_isdigit(cmd[0]))
		return (1);
	if (find_char(cmd, '='))
	{
		temp = put_name_export(cmd);
		if (find_char(temp, '-'))
		{
			free(temp);
			return (1);
		}
		free(temp);
	}
	if (!find_char(cmd, '=' && find_char(cmd, '-')))
		return (1);
	return (0);
}

int	check_error_export(char *cmd)
{
	int		i;

	i = 0;
	if (first_check_var_export(cmd))
		return (1);
	while ((cmd[i] != '\0' && cmd[i] != '=') 
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '+'))
	{
		if (cmd[i] == '+')
		{
			if (cmd[i + 1] != '=')
				return (1);
		}
		i++;
	}
	if (cmd[i] != '\0' && cmd[i] != '=')
		return (1);
	return (0);
}

char	*put_name_export(char *str)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = 0;
	if (!str || !find_char(str, '='))
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

	if (!str || !find_char(str, '='))
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

t_export	*create_new_list_export(char *arg)
{
	t_export	*new_exp;

	new_exp = malloc(sizeof(t_export));
	if (!arg || !new_exp)
		return (NULL);
	new_exp->name = put_name_export(arg);
	if (!new_exp->name)
	{
		free(new_exp);
		return (NULL);
	}
	if (find_char(arg, '='))
	{
		new_exp->value = put_value_export(arg);
		if (new_exp->value == NULL)
			new_exp->value = ft_strdup("\0");
	}
	else
		new_exp->value = NULL;
	new_exp->next = NULL;
	return (new_exp);
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
