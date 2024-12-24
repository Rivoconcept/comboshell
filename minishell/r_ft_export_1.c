/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:27:25 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/24 13:48:54 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**argv;

	i = 0;
	if (cmd[0] == '\0')
		return (1);
	if (!cmd || !find_char(cmd, '=') || (ft_isdigit(cmd[0]) && find_char(cmd,
				'=')))
		return (1);
	argv = ft_split(cmd, '=');
	if (!argv)
		return (1);
	while (argv[0][i] && (ft_isalnum(argv[0][i]) || argv[0][i] == '_'
			|| argv[0][i] == '+'))
		i++;
	if (argv[0] && argv[0][i] != '\0')
	{
		free_array(argv);
		argv = NULL;
		return (1);
	}
	free_array(argv);
	return (0);
}

int	check_var_temp(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd || cmd[0][0] == '\0')
		return (1);
	while (cmd[i] != NULL)
		i++;
	if (i > 1 || check_error_var_temp(cmd[0]))
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
