/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_check_behavior.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/27 10:37:01 by rhanitra         ###   ########.fr       */
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

int	pass_error_test_1(char *s)
{
	if (check_str(s, "<>", "<> "))
		return (printf("minishell: syntax error near unexpected token '<>'\n"));
	if (check_str(s, "><<<", "<> ") || check_str(s, " <<<", "<> ")
		|| !ft_strcmp(s, "<<<<<<"))
		return (printf("minishell: syntax error near unexpected token '<<<'\n"));
	if (check_str(s, " <<", "<> ") || check_str(s, "><<", "<> ")
		|| !ft_strcmp(s, "<<<<<"))
		return (printf("minishell: syntax error near unexpected token '<<'\n"));
	if (check_str(s, " <", "<> ") || check_str(s, "><", "<> ") || !ft_strcmp(s,
			"<<<<"))
		return (printf("minishell: syntax error near unexpected token '<'\n"));
	if (check_str(s, " >>", "<> ") || !ft_strcmp(s, "<>>>") || !ft_strcmp(s,
			">>>>"))
		return (printf("minishell: syntax error near unexpected token '>>'\n"));
	return (0);
}

int	pass_error_test_2(char *s)
{
	if (ft_strcmp(s, "<>>") == 0 || check_str(s, " >", "<> ") || !ft_strcmp(s,
			">>>"))
		return (printf("minishell: syntax error near unexpected token '>'\n"));
	if (!ft_strcmp(s, "||") || (check_input(s, "| <>") && check_str(s, "||",
				"<> |")))
		return (printf("minishell: syntax error near unexpected token '||'\n"));
	if (!ft_strcmp(s, "|") || (check_input(s, "| <>") && check_str(s, "|",
				"<> |")))
		return (printf("minishell: syntax error near unexpected token '|'\n"));
	if (!ft_strcmp(s, "&&"))
		return (printf("minishell: syntax error near unexpected token '&&'\n"));
	if (!ft_strcmp(s, ";;"))
		return (printf("minishell: syntax error near unexpected token ';;'\n"));
	return (0);
}

int	pass_errors_test(char *input, t_params *params)
{
	if (!ft_strncmp(input, "\n", INT_MAX) || !ft_strcmp(input, ":")
	|| check_input_is_all_space(input) || check_input(input, "\t\n\v\f\r\0 "))
		return (params->last_exit_code = 0, 1);
	if (!ft_strcmp(input, "!"))
		return (params->last_exit_code = 1);
	if (check_error_newline(input, params))
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (params->last_exit_code = 2);
	}
	if (pass_error_test_1(input))
		return (params->last_exit_code = 2);
	if (pass_error_test_2(input))
		return (params->last_exit_code = 2);
	return (0);
}