/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_check_behavior.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/26 14:47:01 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_newline(char *s, t_params *params)
{
	int		i;
	char	*base[] = {">", "<", ">>", "<<", "<>", "<<<", "$", "<echo<",
			">>echo>>", "cat >>", "cat <<", NULL};

	i = 0;
	while (base[i] != NULL)
	{
		if (!ft_strcmp(s, base[i]) && ft_strlen(s) == ft_strlen(base[i]))
			return (params->last_exit_code = 2);
		i++;
	}
	return (0);
}

int	pass_error_test_1(char *s, t_params *params)
{
	if (!ft_strncmp(s, "\n", INT_MAX) || !ft_strcmp(s, ":")
		|| check_input_is_all_space(s) || check_input(s, "\t\n\v\f\r\0 "))
		return (params->last_exit_code = 0, 1);
	if (!ft_strcmp(s, "!"))
		return (params->last_exit_code = 2);
	if (check_str(s, "<>", "<> "))
		return (printf("minishell: syntax error near unexpected token '<>'\n"),
			params->last_exit_code = 2);
	if (check_str(s, "><<<", "<> ") || check_str(s, " <<<", "<> ")
		|| !ft_strcmp(s, "<<<<<<"))
		return (printf("minishell: syntax error near unexpected token '<<<'\n"),
			params->last_exit_code = 2);
	if (check_str(s, " <<", "<> ") || check_str(s, "><<", "<> ")
		|| !ft_strcmp(s, "<<<<<"))
		return (printf("minishell: syntax error near unexpected token '<<'\n"),
			params->last_exit_code = 2);
	if (check_str(s, " <", "<> ") || check_str(s, "><", "<> ") || !ft_strcmp(s,
			"<<<<"))
		return (printf("minishell: syntax error near unexpected token '<'\n"),
			params->last_exit_code = 2);
	if (check_str(s, " >>", "<> ") || !ft_strcmp(s, "<>>>") || !ft_strcmp(s,
			">>>>"))
		return (printf("minishell: syntax error near unexpected token '>>'\n"),
			params->last_exit_code = 2);
	return (0);
}

int	pass_error_test_2(char *s, t_params *params)
{
	if (ft_strcmp(s, "<>>") == 0 || check_str(s, " >", "<> ") || !ft_strcmp(s,
			">>>"))
		return (printf("minishell: syntax error near unexpected token '>'\n"),
			params->last_exit_code = 2);
	if (check_error_newline(s, params))
		return (printf("minishell: syntax error near unexpected token 'newline'\n"),
			params->last_exit_code = 2);
	if (!ft_strcmp(s, "||") || (check_input(s, "| <>") && check_str(s, "||",
				"<> |")))
		return (printf("minishell: syntax error near unexpected token '||'\n"),
			params->last_exit_code = 2);
	if (!ft_strcmp(s, "|") || (check_input(s, "| <>") && check_str(s, "|",
				"<> |")))
		return (printf("minishell: syntax error near unexpected token '|'\n"),
			params->last_exit_code = 2);
	if (!ft_strcmp(s, "&&"))
		return (printf("minishell: syntax error near unexpected token '&&'\n"),
			params->last_exit_code = 2);
	if (!ft_strcmp(s, ";;"))
		return (printf("minishell: syntax error near unexpected token ';;'\n"),
			params->last_exit_code = 2);
	return (0);
}

int	pass_errors_test(char *input, t_params *params)
{
	if (pass_error_test_1(input, params))
		return (1);
	if (pass_error_test_2(input, params))
		return (1);
	return (0);
}