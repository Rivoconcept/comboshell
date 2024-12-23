/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_argv_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:26:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 10:45:53 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_other_val(char *str, int *index, t_params *params)
{
	char	*value;

	value = NULL;
	if (str[*index] == '0')
	{
		value = ft_strdup("minishell");
	}
	else if (str[*index] == '?')
	{
		value = ft_itoa(params->last_exit_code);
	}
	else if (ft_isdigit(str[*index]) && str[(*index) - 1] == '$')
	{
		value = ft_strdup("");
	}
	return (value);
}

char	*check_val_env(char *str, int *index, char *env_value, t_params *params)
{
	int		i;
	char	var_env[256];
	char	*other_val;

	i = 0;
	(*index)++;
	other_val = put_other_val(str, index, params);
	if (other_val)
		return (other_val);
	while (str[*index] != '\0' && str[*index] != '"' && str[*index] != '\''
		&& str[*index] != ' ' && str[*index] != '$' && str[*index] != '/')
		var_env[i++] = str[(*index)++];
	(*index)--;
	var_env[i] = '\0';
	env_value = put_env_val(params->myenvp, var_env);
	if (env_value)
		return (env_value);
	else
	{
		return (NULL);
	}
}

void	put_var_env(char *input, int *i, char **temp, t_params *params)
{
	char	*env_value;

	env_value = NULL;
	if (in_double_quote(input))
		*temp = check_val_env(input, i, env_value, params);
	else if (in_single_quote(input))
	{
		if (input[*i - 1] == '\'' && *i > 1)
			*temp = check_val_env(input, i, env_value, params);
		else
			*temp = ft_strdup("$");
	}
	else if (var_in_apostrophe(input, *i))
		*temp = ft_strdup("$");
	else if (pure_quote(input))
		*temp = check_val_env(input, i, env_value, params);
	else if (input != NULL && !pure_quote(input) && !pure_apostrophe(input)
		&& !in_double_quote(input) && !in_single_quote(input))
	{
		*temp = check_val_env(input, i, env_value, params);
	}
}

int	is_in_myenvp(char *temp, t_env *myenvp)
{
	t_env	*current;

	current = myenvp;
	while (current)
	{
		if (temp == current->value)
			return (1);
		current = current->next;
	}
	return (0);
}
