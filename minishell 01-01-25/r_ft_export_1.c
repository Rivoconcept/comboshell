/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:27:25 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 09:57:04 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	print_export(t_params *params)
{
	t_export	*current;

	current = params->myexport;
	if (current == NULL)
		return (1);
	while (current != NULL)
	{
		if (!current->value)
			printf("declare -x %s\n", current->name);
		else
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

int	check_error_var_temp(char *cmd)
{
	int		i;

	i = 0;
	if (!cmd || cmd[0] == '\0' || cmd[0] == '+' || cmd == NULL \
		|| ft_isdigit(cmd[0]) || !find_char(cmd, '='))
		return (0);
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '+'))
	{
		if (cmd[i] == '+')
		{
			if (cmd[i + 1] != '=')
				return (0);
		}
		i++;
	}
	if (cmd[i] != '=')
		return (0);
	return (1);
}

void	clean_export(char *exist_value, char *enter_value, char *name)
{
	if (enter_value || enter_value != NULL)
		free(enter_value);
	if (exist_value || exist_value != NULL)
		free(exist_value);
	if (name || name != NULL)
		free(name);
}
