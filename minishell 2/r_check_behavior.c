/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_check_behavior.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 15:28:01 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_newline(char *s)
{
	int		i;
	char	*base[13];

	base[0] = ">";
	base[1] = "<";
	base[2] = ">>";
	base[3] = "<<";
	base[4] = "<>";
	base[5] = "<<<";
	base[6] = "$";
	base[7] = "< echo <";
	base[8] = "> echo >";
	base[9] = ">> echo >>";
	base[10] = "cat >>";
	base[11] = "cat <<";
	base[12] = NULL;
	i = 0;
	while (base[i] != NULL)
	{
		if (!ft_strncmp(s, base[i], ft_strlen(s))
			&& ft_strlen(s) == ft_strlen(base[i]))
			return (1);
		i++;
	}
	return (0);
}

int isoperators(char *cmd)
{
    int     i;

    i = 0;
    while (cmd[i] != '\0' && is_operator(cmd[i]))
        i++;
    if (cmd[i] == '\0')
        return (1);
    return (0);
}

int check_return_zero(char *input, t_params *params)
{
    int i;

    if (!input || !params)
        return (0);
    i = 0;
    while (input[i] && ft_is_space(input[i]))
        i++;
    if (input[i] == '\0' || input[i] == ':')
    {
        params->last_exit_code = 0;
        return (1);
    }
    return (0);
}

int check_exclamation(char *input, t_params *params)
{
    int i;

    if (!input || !params)
        return (0);
    i = 0;
    while (input[i] && ft_is_space(input[i]))
        i++;
    if (input[i] == '!')
    {
        params->last_exit_code = 1;
        return (1);
    }
    return (0);
}

int check_error_pipe(char **cmd, t_params *params)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (check_return_zero(cmd[i], params))
			return (1);
		else if ((isoperators(cmd[i]) && cmd[i + 1] ==  NULL)
            && strncmp(cmd[i], "|", ft_strlen(cmd[i])))
		{
			params->last_exit_code = 2;
			return (printf("minishell: syntax error near unexpected token\n") + 1);
		}
		else if (check_exclamation(cmd[i], params) && cmd[i + 1] == NULL && !cmd[i - 1])
        	return (1);
		else if ((i == 0 && (!ft_strncmp(cmd[i], "|", 2) || !ft_strncmp(cmd[i], "||", 3)))
			|| (i > 0 && !ft_strncmp(cmd[i], "|", 1) && cmd[i + 1] == NULL)
			|| (isoperators(cmd[i]) && (ft_strlen(cmd[i]) > 2 || cmd[i][1] == '|')))
		{
			params->last_exit_code = 2;
			return (printf("minishell: syntax error near unexpected token\n"));
		}
		i++;
	}
	return (0);
}

int check_general_errors(char *s, char **cmd, t_params *params)
{
    if (!s || !params)
        return (0);
    else if (check_return_zero(s, params))
        return (1);
	else if (check_error_pipe(cmd, params))
		return (1);
    return (0);
}
