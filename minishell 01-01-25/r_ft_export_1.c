/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:27:25 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/01 18:40:51 by rhanitra         ###   ########.fr       */
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

int	check_errors_exp(char *cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (!cmd || cmd[0] == '\0' || cmd[0] == '+' || !find_char(cmd, '=')
		|| cmd == NULL || ft_isdigit(cmd[0]))
		return (1);
	if (cmd[0] == '\'' || cmd[0] == '"')
	{
		i++;
		quote = 1;
	}
	if (quote && (ft_isdigit(cmd[i]) || (!ft_isalpha(cmd[i]) \
		&& cmd[i] != '_')))
		return (1);
	i++;
	while (quote && cmd[i] != '=' && (cmd[i] != '\'' || cmd[i] != '"')
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '+')
		&& cmd[i] != ' ')
		i++;
	if (cmd[i] != '=')
		return (1);
	return (0);
}

int	check_error_var_temp(char *cmd, t_params *params)
{
	int		i;
	char	**argv;

	i = 0;
	if (check_errors_exp(cmd))
		return (0);
	argv = ft_split(cmd, '=');
	if (!argv)
		return (0);
	i++;
	while (argv[0][i] && (ft_isalnum(argv[0][i]) || argv[0][i] == '_'
			|| argv[0][i] == '+'))
		i++;
	if (argv[0] && argv[0][i] != '\0')
	{
		free_array(argv);
		argv = NULL;
		return (0);
	}
	free_array(argv);
	free_array(params->parsed);
	if (params->command)
		free_list_cmd(params->command);
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
