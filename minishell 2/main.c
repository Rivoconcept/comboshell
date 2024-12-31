/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:44:10 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 21:33:57 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_ctrl_d(char *input, t_params *params)
{
	int	last_exit_status;

	last_exit_status = 0;
	if (!input)
	{
		last_exit_status = params->last_exit_code;
		close(params->fd_in);
		close(params->fd_out);
		printf("exit\n");
		free(input);
		free_list_env(params->myenvp);
		free_list_export(params->myexport);
		free_array(params->envp);
		free(params);
		exit(last_exit_status);
	}
}

int	handle_history(char *input)
{
	if (input)
	{
		add_history(input);
		push_history(input);
	}
	return (0);
}
int	handle_command_1(char *input, t_params *params)
{
	params->new_input = format_input(input);
	free(input);
	input = NULL;
	if (!params->new_input)
		exit(EXIT_FAILURE);
	params->parsed = parse_command(params->new_input);
	if (check_general_errors(params->new_input, params->parsed, params))
	{
		free(params->new_input);
		free_array(params->parsed);
		return (1);
	}
	free(params->new_input);
	params->command = init_command(params->parsed);
	return (0);
}

int	handle_command_2(t_params *params)
{
	if (check_error_var_temp(params->parsed[0]) && !params->parsed[1])
	{
		free_array(params->parsed);
		if (params->command)
			free_list_cmd(params->command);
		return (1);
	}
	free_array(params->parsed);
	params->parsed = NULL;
	if(manage_here(params))
	{
		if (params->command)
			free_list_cmd(params->command);
		return (1);
	}
	manage_less(params);
	/*if (manage_less(params))
	{
		if (params->command)
			free_list_cmd(params->command);
		return (1);
	}*/
	manage_red(params);
	if (!params->command)
		return (1);
	format_all_variable(params);
	delete_cmd_null(params);
	if (!params->command)
		return (1);
	delete_null_in_argv(params);
	if (!params->command)
		return (1);
	delete_quotes(params);
	format_cmd(params);
	if (check_errors(params))
	{
		if (params->command)
			free_list_cmd(params->command);
		return (1);
	}
	exec_cmd(params);
	params->rank_cmd = 0;
	if (params->command)
		free_list_cmd(params->command);
	return (0);
}
int handle_ctrl_c(t_params *params, char *input)
{
	if (g_sig_num == SIGINT)
	{
		dup2(params->fd_in, STDIN_FILENO);
		free(input);
		g_sig_num = 0;
		params->last_exit_code = 130;
		return (1);
	}
	return (0);
}
void	run_minishell(t_params *params)
{
	char	*input;

	input = NULL;
	signal(SIGQUIT, SIG_IGN);
	params->fd_in = dup(STDIN_FILENO);
	params->fd_out = dup(STDOUT_FILENO);
	while (1)
	{
		signal_handlers(SIGINT);
		g_sig_num = 0;
		input = readline("$> ");
		if (handle_ctrl_c(params, input))
			continue ;
		clean_ctrl_d(input, params);
		handle_history(input);
		if (handle_command_1(input, params))
			continue ;
		if (handle_command_2(params))
			continue;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_params	*params;

	(void)argc;
	(void)argv;
	params = create_list_params(envp);
	if (!params)
		return (1);
	ignore_leaks_readline();
	add_old_history();
	run_minishell(params);
	cleanup_and_exit(params, 0);
	return (0);
}