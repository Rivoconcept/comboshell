/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_check_behavior.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 15:46:06 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_newline(char *s)
{
	int		i;
	char	*base[12];

	base[0] = ">";
	base[1] = "<";
	base[2] = ">>";
	base[3] = "<<";
	base[4] = "<>";
	base[5] = "<<<";
	base[6] = "$";
	base[7] = "<echo<";
	base[8] = ">>echo>>";
	base[9] = "cat >>";
	base[10] = "cat <<";
	base[11] = NULL;
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

int	pass_error_test_1(char *s)
{
	if (check_str(s, "<>", "<> ") && find_char(s, '<'))
		return (printf("minishell: syntax error near unexpected \
		token '<>'\n"));
	if ((check_str(s, "><<<", "<> ") || check_str(s, " <<<", "<> ")
		|| !ft_strncmp(s, "<<<<<<", ft_strlen("<<<<<<"))) && find_char(s, '<'))
		return (printf("minishell: syntax error near unexpected \
		token '<<<'\n"));
	if ((check_str(s, " <<", "<> ") || check_str(s, "><<", "<> ")
		|| !ft_strncmp(s, "<<<<<", ft_strlen("<<<<<"))) && find_char(s, '<'))
		return (printf("minishell: syntax error near unexpected \
		token '<<'\n"));
	if ((check_str(s, " <", "<> ") || check_str(s, "><", "<> ") || !ft_strncmp(s,
			"<<<<", ft_strlen("<<<<"))) && find_char(s, '<'))
		return (printf("minishell: syntax error near unexpected \
		token '<'\n"));
	if (check_str(s, " >>", "<> ") || !ft_strncmp(s, "<>>>", ft_strlen("<>>>"))
		|| !ft_strncmp(s, ">>>>", ft_strlen(">>>>")))
		return (printf("minishell: syntax error near unexpected \
		token '>>'\n"));
	return (0);
}

int	pass_error_test_2(char *s)
{
	if ((ft_strncmp(s, "<>>", ft_strlen(s)) == 0 || check_str(s, " >", "<> ")
		|| !ft_strncmp(s, ">>>", ft_strlen(">>>"))) && find_char(s, '>'))
		return (printf("minishell: syntax error near unexpected token '>'\n"));
	if (!ft_strncmp(s, "||", 2) || (check_input(s, "| <>") && check_str(s, "||",
				"<> |")))
		return (printf("minishell: syntax error near unexpected token '||'\n"));
	if (!ft_strncmp(s, "|", 1) || (check_input(s, "| <>") && check_str(s, "|",
				"<> |")))
		return (printf("minishell: syntax error near unexpected token '|'\n"));
	if (!ft_strncmp(s, "&&", ft_strlen(s)) && find_char(s, '&'))
		return (printf("minishell: syntax error near unexpected token '&&'\n"));
	if ((!ft_strncmp(s, ";;", ft_strlen(s))) && find_char(s, ';'))
		return (printf("minishell: syntax error near unexpected token ';;'\n"));
	return (0);
}
int	pass_errors_test_3(char *s, t_params *params)
{
	char	*temp;

	temp = NULL;
	if (!ft_strncmp(s, "\n", INT_MAX) || !ft_strcmp(s, ":")
		|| (check_is_all_space(s) && !find_char(s, '\'') && !find_char(s, '"')))
	{
		params->last_exit_code = 0;
		return (1);
	}
	if (check_is_all_space(s) && (find_char(s, '\'') || find_char(s, '"')))
	{
		temp = format_quotes(s);
		printf("minishell: %s: command not found\n", temp);
		free(temp);
		return (params->last_exit_code = 127);
	}
	if (!ft_strcmp(s, "!"))
		return (params->last_exit_code = 1);
	if (check_error_newline(s))
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (params->last_exit_code = 2);
	}
	return (0);
}
int	check_general_errors(char *s, t_params *params)
{
	int		i;
	char	**cmd;

	i = 0;
	if (pass_error_test_1(s))
		return (params->last_exit_code = 2);
	if (pass_error_test_2(s))
		return (params->last_exit_code = 2);
	cmd = ft_split(s, '|');
	if (!cmd || !cmd[0])
	{
		free_array(cmd);
		return (0);
	}
	while (cmd[i] != NULL)
	{
		if (pass_errors_test_3(cmd[i], params))
		{
			free_array(cmd);
			return (1);
		}
		i++;
	}
	free_array(cmd);
	return (0);
}
