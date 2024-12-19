/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:44:10 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/18 15:25:43 by rhanitra         ###   ########.fr       */
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

/*void	copy_argv(char **argv, int x[3], char ***temp, t_cmd **cmd)
{
	(*temp)[(x[1])++] = strdup(argv[x[0]]);
	if (!argv[x[0] + 1])
	{
		(*temp)[x[1]] = NULL;
		*cmd = add_command(*cmd, *temp);
		*temp = NULL;
	}
}*/

void	copy_argv(char **argv, int x[3], char ***temp, t_cmd **cmd)
{
	(*temp)[x[1]++] = ft_strdup(argv[x[0]]);
	if (!(*temp)[x[1] - 1])
	{
		perror("ft_strdup");
		free_list_cmd(*cmd);
		exit(EXIT_FAILURE);
	}
	if (!argv[x[0] + 1])
	{
		(*temp)[x[1]] = NULL;
		*cmd = add_command(*cmd, *temp);
		free(*temp);
		*temp = NULL;
	}
}

/*int add_separator(char **argv, int x[3], char ***temp, t_cmd **cmd)
{
    if (*temp)
    {
        *temp[x[1]] = NULL;
        *cmd = add_command(*cmd, *temp);
        *temp = NULL;
        x[2] = 0;
    }
    *temp = malloc(sizeof(char *) * 2);
    if (!(*temp))
    {
        perror("malloc");
        free_list_cmd(*cmd);
        return (1);
    }
    *temp[0] = strdup(argv[x[0]]);
    *temp[1] = NULL;
    *cmd = add_command(*cmd, *temp);
    *temp = NULL;
    x[2] = 0;
    return (0);
}*/

t_cmd	*init_command(char **argv)
{
	t_cmd	*cmd;
	char	**temp;
	int     x[3];

	cmd = NULL;
	temp = NULL;
	x[0] = 0;
    x[1] = 0;
    x[2] = 0;
	while (argv[x[0]] != NULL)
	{
		if (!x[2] && ft_strcmp(argv[x[0]], "|") != 0)
		{
			x[2] = put_size(argv, x[0]);
			temp = malloc(sizeof(char *) * (x[2] + 1));
			if (!temp)
				return (free_list_cmd(cmd), perror("malloc"), NULL);
			x[1] = 0;
		}
		if (ft_strcmp(argv[x[0]], "|") == 0)
		{
			if (temp)
			{
				temp[x[1]] = NULL;
				cmd = add_command(cmd, temp);
				temp = NULL;
				x[2] = 0;
			}
			temp = malloc(sizeof(char *) * 2);
			if (!temp)
				return (free_list_cmd(cmd), perror("malloc"), NULL);
			temp[0] = ft_strdup(argv[x[0]]);
			temp[1] = NULL;
			cmd = add_command(cmd, temp);
			temp = NULL;
			x[2] = 0;
		}
		else
		{
			temp[(x[1])++] = ft_strdup(argv[x[0]]);
			if (!argv[x[0] + 1])
			{
				temp[x[1]] = NULL;
				cmd = add_command(cmd, temp);
				temp = NULL;
			}
		}
		(x[0])++;
	}
	return (cmd);
}

/*t_cmd *init_command(char **argv)
{
	t_cmd	*cmd;
	char	**temp;
	int		i;
	int		j;
	int		size;
	int		i;
	int		list_num;

	cmd = NULL;
	temp = NULL;
	i = 0;
	j = 0;
	size = 0;
	while (argv[i] != NULL)
	{
		if (!size && strcmp(argv[i], "|") != 0)
		{
			size = put_size(argv, i);
			temp = malloc(sizeof(char *) * (size + 1));
			if (!temp)
				return (free_list_cmd(cmd), perror("malloc"), NULL);
			j = 0;
		}
		if (strcmp(argv[i], "|") == 0)
		{
			if (temp)
			{
				temp[j] = NULL;
				cmd = add_command(cmd, temp);
				temp = NULL;
				size = 0;
			}
			temp = malloc(sizeof(char *) * 2);
			if (!temp)
				return (free_list_cmd(cmd), perror("malloc"), NULL);
			temp[0] = strdup(argv[i]);
			temp[1] = NULL;
			cmd = add_command(cmd, temp);
			temp = NULL;
			size = 0;
		}
		else
		{
			temp[j++] = strdup(argv[i]);
			if (!argv[i + 1])
			{
				temp[j] = NULL;
				cmd = add_command(cmd, temp);
				temp = NULL;
			}
		}
		i++;
	}
	return (cmd);
}*/

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

void	run_minishell(t_params *params)
{
	char	**parsed;
	char	*input;
	char	*new_input;

	parsed = NULL;
	input = NULL;
	new_input = NULL;
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
		if (input)
			add_history(input);
		if (g_sig_num == SIGINT)
			params->last_exit_code = 130;
		new_input = format_input(input);
		if (!new_input)
			exit(EXIT_FAILURE);
		free(input);
		//printf("%s\n", new_input);
		if (!new_input || ft_strcmp(new_input, "exit") == 0)
		{
			printf("%d\n", params->last_exit_code);
			free(new_input);
			break ;
		}
		parsed = parse_command(new_input);
		format_variable(parsed, params);
		del_quotes(parsed);
		if (put_var_temp(parsed, params))
		{
			free(new_input);
			free_array(parsed);
			continue ;
		}
		//print_argv(parsed);
		params->command = init_command(parsed);
		free_array(parsed);
		free(new_input);
		format_cmd(params);
		if (check_errors(params))
		{
			free_list_cmd(params->command);
			params->command = NULL;
			continue ;
		}

		//print_cmd(params);
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
	run_minishell(params);
	cleanup_and_exit(params, 0);
	return (0);
}
