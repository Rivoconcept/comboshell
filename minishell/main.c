/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:44:10 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/27 11:09:03 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_num = 0;

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
int add_separator(int var[3], char ***temp, t_cmd *cmd, char **argv)
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

int initialize_cmd(int var[3], char ***temp, t_cmd *cmd, char **argv)
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

void check_end_cmd(int var[3], char ***temp, t_cmd **cmd, char **argv)
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
void clean_cmd(t_cmd **cmd, char ***temp)
{
	reset_cmd_flags(*cmd);
    if (*temp)
        free(*temp);
}

t_cmd *init_command(char **argv)
{
    t_cmd *cmd = NULL;
    char **temp = NULL;
    int var[3];

    var[0] = 0;
    var[1] = 0;
    var[2] = 0;
    while (argv[var[0]] != NULL)
    {
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
	int i;
    int list_num = 1;
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

void print_argv(char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        // ft_putstr_fd(argv[i], 2);
        // ft_putstr_fd("\n", 2);
        i++;
    }

}
void print_cmd(t_params *params)
{
    t_cmd *current = params->command;

    while (current != NULL)
    {
        print_argv(current->cmd);
        current = current->next;
    }
}
void	run_minishell(t_params *params)
{
	char	*input;

	input = NULL;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_sig_num = 0;
		input = readline("$> ");
		if (!input)
		{
			printf("exit\n");
			cleanup_and_exit(params, params->last_exit_code);
		}
		if (pass_errors_test(input, params))
		{
			free(input);
			continue ;	
		}
		if (input)
		{
			add_history(input);
			push_history(input);
		}
		if (g_sig_num == SIGINT)
			params->last_exit_code = 130;
		params->new_input = format_input(input);
		free(input);
		input = NULL;
		if (!params->new_input)
			exit(EXIT_FAILURE);
		params->parsed = parse_command(params->new_input);
		format_variable(params->parsed, params);
		// josia modification init_commad
		params->command = init_command(params->parsed);
		format_cmd(params);
		//josia
		manage_here(params);
		//josia mod free_list_cmd
		free_list_cmd(params->command);
		del_quotes(params->parsed);
		if (check_var_temp(params->parsed))
		{
			free(params->new_input);
			free_array(params->parsed);
			continue ;
		}
		//print_argv(parsed);
		params->command = init_command(params->parsed);
		free_array(params->parsed);
		free(params->new_input);
		format_cmd(params);
		//josia
		manage_less(params);
		if (check_errors(params))
		{
			free_list_cmd(params->command);
			params->command = NULL;
			continue ;
		}
		//josia
		manage_red(params);
		exec_cmd(params);
		free_list_cmd(params->command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_params	*params;

	(void)argc;
	(void)argv;
	// signal_handlers(SIGCHLD);
	signal_handlers(SIGINT);
	params = create_list_params(envp);
	if (!params)
		return (1);
	ignore_leaks_readline();
	add_old_history();
	run_minishell(params);
	cleanup_and_exit(params, 0);
	return (0);
}
