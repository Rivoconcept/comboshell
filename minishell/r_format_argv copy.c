/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_argv copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:26:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/22 13:50:30 by rhanitra         ###   ########.fr       */
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
	else if ((var_in_apostrophe(str, *index - ft_strlen(var_env))
			&& !in_double_quote(str)) || in_double_quote(str))
		return (NULL);
	else
		return (*index -= ft_strlen(var_env), NULL);
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
			*temp = "$";
	}
	else if (var_in_apostrophe(input, *i))
		*temp = "$";
	else if (pure_quote(input))
		*temp = check_val_env(input, i, env_value, params);
	else if (!pure_quote(input) && !pure_apostrophe(input)
		&& !in_double_quote(input) && !in_single_quote(input))
	{
		*temp = check_val_env(input, i, env_value, params);
	}
}

char	*format_var_env(char *arg, t_params *params)
{
	int			i[3] = {-1, 0};
	char		*temp;
	static char	new_str[1024];

	while (arg[++i[0]] != '\0')
	{
		if (arg[i[0]] == '$')
		{
			temp = NULL;
			put_var_env(arg, &i[0], &temp, params);
			if (temp)
				copy_var_env(temp, new_str, &i[1]);
			else if (!in_double_quote(arg))
				new_str[(i[1])++] = '$';
			// if (temp && temp != new_str && temp != arg)
			// 	free(temp);
		}
		else
			new_str[(i[1])++] = arg[i[0]];
		new_str[i[1]] = '\0';
	}
	return (new_str);
}


void	format_variable(char **argv, t_params *params)
{
	int		i;
	char	*tmp;

	i = 0;
	while (argv[i] != NULL)
	{
		tmp = ft_strdup(format_var_env(argv[i], params));
		free(argv[i]);
		argv[i] = tmp;
		i++;
	}
}