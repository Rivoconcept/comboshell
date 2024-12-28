/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:44:10 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 19:37:53 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	put_size(char **argv, int i)
{
	int	count;

	count = 0;
	while (argv[i + count])
	{
		if (argv[i + count] == NULL || ft_strcmp(argv[i + count], "|") == 0)
			break ;
		count++;
	}
	return (count);
}

int	add_separator(int var[3], char ***temp, t_cmd *cmd, char **argv)
{
	if (*temp && var[1] > 0)
	{
		(*temp)[var[1]] = NULL;
		cmd = add_command(cmd, *temp);
		*temp = NULL;
		var[2] = 0;
	}
	*temp = malloc(sizeof(char *) * 2);
	if (!*temp)
		return (free_list_cmd(cmd), perror("malloc"), 1);
	(*temp)[0] = ft_strdup(argv[var[0]]);
	if (!(*temp)[0])
		return (free_list_cmd(cmd), free(*temp), perror("strdup"), 1);
	(*temp)[1] = NULL;
	cmd = add_command(cmd, *temp);
	*temp = NULL;
	return (0);
}

int	initialize_cmd(int var[3], char ***temp, t_cmd *cmd, char **argv)
{
	if (!var[2])
	{
		var[2] = put_size(argv, var[0]);
		*temp = malloc(sizeof(char *) * (var[2] + 1));
		if (!*temp)
			return (free_list_cmd(cmd), perror("malloc"), 1);
		var[1] = 0;
	}
	if (argv[var[0]][0] != '\0')
	{
		(*temp)[var[1]] = ft_strdup(argv[var[0]]);
		if (!(*temp)[var[1]])
			return (free_list_cmd(cmd), free(temp), perror("strdup"), 1);
		var[1]++;
	}
	return (0);
}

void	check_end_cmd(int var[3], char ***temp, t_cmd **cmd, char **argv)
{
	if (!argv[var[0] + 1] || ft_strncmp(argv[var[0] + 1], "|", 1) == 0)
	{
		if (*temp && var[1] > 0)
		{
			(*temp)[var[1]] = NULL;
			(*cmd) = add_command((*cmd), *temp);
			*temp = NULL;
			var[2] = 0;
		}
	}
}
void	clean_cmd(t_cmd **cmd, char ***temp)
{
	reset_cmd_flags(*cmd);
	if (*temp)
		free(*temp);
}

t_cmd	*init_command(char **argv)
{
	t_cmd	*cmd;
	char	**temp;
	int		var[3];

	cmd = NULL;
	temp = NULL;
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	while (argv[var[0]] != NULL)
	{
		if (!argv[var[0]] || argv[var[0]][0] == '\0')
        {
            var[0]++;
            continue;
        }
		if (ft_strcmp(argv[var[0]], "|") == 0)
		{
			if (add_separator(var, &temp, cmd, argv))
				return (NULL);
		}
		else
		{
			if (initialize_cmd(var, &temp, cmd, argv))
				return (NULL);
			check_end_cmd(var, &temp, &cmd, argv);
		}
		var[0]++;
	}
	return (clean_cmd(&cmd, &temp), cmd);
}

void	print_list(t_cmd *command)
{
	int	i;
	int	list_num;

	list_num = 1;
	while (command)
	{
		printf("Liste%d: ", list_num++);
		i = 0;
		while (command->cmd[i])
		{
			printf("%s ", command->cmd[i]);
			i++;
		}
		printf("\n");
		command = command->next;
	}
}

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		printf("%s\n", argv[i]);
		// ft_putstr_fd(argv[i], 2);
		// ft_putstr_fd("\n", 2);
		i++;
	}
}
void	print_cmd(t_params *params)
{
	t_cmd	*current;

	current = params->command;
	while (current != NULL)
	{
		print_argv(current->cmd);
		current = current->next;
	}
	printf("*********************************************\n");
}
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

/*int	add_cmd_in_params(char *input, t_params *params)
{
	params->new_input = format_input(input);
	free(input);
	input = NULL;
	if (!params->new_input)
		exit(EXIT_FAILURE);
	params->parsed = parse_command(params->new_input);
	format_variable(params->parsed, params);
	// josia modification init_commad
	//print_argv(params->parsed);
	del_quotes(params->parsed);
	params->command = init_command(params->parsed);
	print_cmd(params->command);
	format_cmd(params);
	
	// josia
	if(manage_here(params))
	{
		free(params->new_input);
		free_array(params->parsed);
		free_list_cmd(params->command);
		return (1);
	}
	// josia mod free_list_cmd

	if (check_var_temp(params->parsed))
	{
		free(params->new_input);
		free_array(params->parsed);
		return (1);
	}
	// print_argv(parsed);

	free_array(params->parsed);
	free(params->new_input);
	//format_cmd(params);
	manage_less(params);
	manage_red(params);
	format_cmd(params);
	return (0);
}*/

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
		if (g_sig_num == SIGINT)
		{
			dup2(params->fd_in, STDIN_FILENO);
			free(input);
			g_sig_num = 0;
			params->last_exit_code = 130;
			continue;
		}
		clean_ctrl_d(input, params);
		handle_history(input);
		if (check_general_errors(input, params))
		{
			free(input);
			continue ;
		}
		// if (add_cmd_in_params(input, params))
		// 	continue ;
		params->new_input = format_input(input, "|");
		free(input);
		input = NULL;
		if (!params->new_input)
			exit(EXIT_FAILURE);
		printf("%s\n", params->new_input);
		free(params->new_input);		
		continue;
		params->parsed = parse_command(params->new_input);
		free(params->new_input);
		// josia modification init_commad
		// format_variable(params->parsed, params);
		// del_quotes(params->parsed);
		// print_argv(params->parsed);
		// free_array(params->parsed);
		// continue ;
		//del_quotes(params->parsed);
		params->command = init_command(params->parsed);
		if (check_error_var_temp(params->parsed[0]) && !params->parsed[1])
		{
			free_list_cmd(params->command);
			continue ;
		}
		free_array(params->parsed);

		// delete_cmd_null(params);
		//print_cmd(params);

		// print_cmd(params);
		// josia
		
		// josia mod free_list_cmd

		if(manage_here(params)) 
		{
			free_list_cmd(params->command);
			continue ;
		}

		manage_less(params);
		manage_red(params);
		format_cmd(params);
		//print_cmd(params);

		//print_cmd(params);
		// if ((params->command && check_errors(params)) || !params->command)
		// {
		// 	free_list_cmd(params->command);
		// 	params->command = NULL;
		// 	continue ;
		// }
		// print_cmd(params);
		// 		free_list_cmd(params->command);
		// continue ;
		format_all_variable(params);
		delete_quotes(params);
		format_cmd(params);
		// print_list(params->command);
		delete_cmd_null(params);
		delete_null_in_argv(params);
		exec_cmd(params);
		params->rank_cmd = 0;
		free_list_cmd(params->command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_params	*params;

	(void)argc;
	(void)argv;
	// signal_handlers(SIGCHLD);
	params = create_list_params(envp);
	if (!params)
		return (1);
	ignore_leaks_readline();
	add_old_history();
	run_minishell(params);
	cleanup_and_exit(params, 0);
	return (0);
}