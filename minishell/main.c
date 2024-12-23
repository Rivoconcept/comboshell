/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:44:10 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 23:58:36 by rhanitra         ###   ########.fr       */
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
/*
int add_separator(int var[3], char ***temp, t_cmd *cmd, char ***argv)
{
	if (*temp && j > 0)
	{
		*temp[j] = NULL;
		cmd = add_command(cmd, *temp);
		temp = NULL;
		size = 0;
	}
	*temp = malloc(sizeof(char *) * 2);
	if (!*temp)
		return (free_list_cmd(cmd), perror("malloc"), 1);
	*temp[0] = ft_strdup(*argv[i]);
	if (!*temp[0])
		return (free_list_cmd(cmd), free(*temp), perror("strdup"), 1);
	*temp[1] = NULL;
	cmd = add_command(cmd, *temp);
	*temp = NULL;
	return (0);
}
*/
/*int initialize_commande(int var[3], char ***temp, t_cmd *cmd, char **argv)
{
		// Initialisation de la commande
	if (!size)
	{
		size = put_size(argv, i);
		*temp = malloc(sizeof(char *) * (size + 1));
		if (!*temp)
			return (free_list_cmd(cmd), perror("malloc"), 1);
		j = 0;
	}

	// Ajout des arguments à la commande
	if (argv[i][0] != '\0') // Ignorer les arguments vides
	{
		*temp[j] = strdup(argv[i]);
		if (!temp[j])
			return (free_list_cmd(cmd), free(*temp), perror("strdup"), 1);
		(j)++;
	}

	// Fin de la commande
	if (!argv[i + 1] || strcmp(argv[i + 1], "|") == 0)
	{
		if (*temp && j > 0)
		{
			*temp[j] = NULL;
			cmd = add_command(cmd, *temp);
			*temp = NULL;
			size = 0;
		}
	}
	return (0);
}*/

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
        (*temp)[var[1]] = strdup(argv[var[0]]);
        if (!(*temp)[var[1]])
            return (free_list_cmd(cmd), free(temp), perror("strdup"), 1);
        var[1]++;
    }
    return (0);
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
            if (!argv[var[0] + 1] || ft_strncmp(argv[var[0] + 1], "|", 1) == 0)
            {
                if (temp && var[1] > 0)
                {
                    temp[var[1]] = NULL;
                    cmd = add_command(cmd, temp);
                    temp = NULL;
                    var[2] = 0;
                }
            }
        }
        var[0]++;
    }
    reset_cmd_flags(cmd);
    if (temp)
        free(temp);
    return (cmd);
}

	
/*t_cmd *init_command(char **argv)
{
    t_cmd *cmd = NULL;
    char **temp = NULL;
	int		var[3];

	var[0] = 0;
	var[1] = 0;
	var[2] = 0;

	    // int i = 0, j = 0, size = 0;
    while (argv[var[0]] != NULL)
    {
        if (strcmp(argv[var[0]], "|") == 0)
        {
			if (add_separator(&var[3], &temp, cmd, argv))
				return (NULL);*/
            //  Ajout de la commande courante (si valide)
            /*if (temp && j > 0)
            {
                temp[j] = NULL;
                cmd = add_command(cmd, temp);
                temp = NULL;
                size = 0;
            }

            // Ajout du séparateur "|"
			temp = malloc(sizeof(char *) * 2);
			if (!temp)
				return (free_list_cmd(cmd), perror("malloc"), NULL);
			temp[0] = ft_strdup(argv[i]);
			if (!temp[0])
				return (free_list_cmd(cmd), free(temp), perror("strdup"), NULL);
			temp[1] = NULL;
			cmd = add_command(cmd, temp);
			temp = NULL;*/
       /* }
        else
        {
            // Initialisation de la commande
            if (!var[2])
            {
                var[2] = put_size(argv, var[0]);
                temp = malloc(sizeof(char *) * (var[2] + 1));
                if (!temp)
                    return (free_list_cmd(cmd), perror("malloc"), NULL);
                var[1] = 0;
            }

            // Ajout des arguments à la commande
            if (argv[var[0]][0] != '\0') // Ignorer les arguments vides
            {
                temp[var[1]] = strdup(argv[var[0]]);
                if (!temp[var[1]])
                    return (free_list_cmd(cmd), free(temp), perror("strdup"), NULL);
                var[1]++;
            }

            // Fin de la commande
            if (!argv[var[0] + 1] || strcmp(argv[var[0] + 1], "|") == 0)
            {
                if (temp && var[1] > 0)
                {
                    temp[var[1]] = NULL;
                    cmd = add_command(cmd, temp);
                    temp = NULL;
                    var[2] = 0;
                }
            }
        }
        var[0]++;
    }
	reset_cmd_flags(cmd);
    // Libérer `temp` en cas de fuite mémoire
    if (temp)
        free(temp);

    return cmd;
}*/


/*t_cmd *init_command(char **argv)
{
    t_cmd *cmd = NULL;
    char **temp = NULL;
    int i = 0, j = 0, size = 0;

    while (argv[i] != NULL)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            // Ajout de la commande courante (si valide)
            if (temp && j > 0)
            {
                temp[j] = NULL;
                cmd = add_command(cmd, temp);
                temp = NULL;
                size = 0;
            }

            // Ajout du séparateur "|"
            temp = malloc(sizeof(char *) * 2);
            if (!temp)
                return (free_list_cmd(cmd), perror("malloc"), NULL);
            temp[0] = strdup(argv[i]);
            if (!temp[0])
                return (free_list_cmd(cmd), free(temp), perror("strdup"), NULL);
            temp[1] = NULL;
            cmd = add_command(cmd, temp);
            temp = NULL;
        }
        else
        {
            // Initialisation de la commande
            if (!size)
            {
                size = put_size(argv, i);
                temp = malloc(sizeof(char *) * (size + 1));
                if (!temp)
                    return (free_list_cmd(cmd), perror("malloc"), NULL);
                j = 0;
            }

            // Ajout des arguments à la commande
            if (argv[i][0] != '\0') // Ignorer les arguments vides
            {
                temp[j] = strdup(argv[i]);
                if (!temp[j])
                    return (free_list_cmd(cmd), free(temp), perror("strdup"), NULL);
                j++;
            }

            // Fin de la commande
            if (!argv[i + 1] || strcmp(argv[i + 1], "|") == 0)
            {
                if (temp && j > 0)
                {
                    temp[j] = NULL;
                    cmd = add_command(cmd, temp);
                    temp = NULL;
                    size = 0;
                }
            }
        }
        i++;
    }

    // Libérer `temp` en cas de fuite mémoire
    if (temp)
        free(temp);

    return cmd;
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
		if (pass_errors_test(input))
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
		new_input = format_input(input);
		if (!new_input)
			exit(EXIT_FAILURE);
		free(input);
		parsed = parse_command(new_input);
		format_variable(parsed, params);
		// josia modification init_commad
		params->command = init_command(parsed);
		format_cmd(params);
		//josia
		manage_here(params);
		//josia mod free_list_cmd
		free_list_cmd(params->command);
		del_quotes(parsed);
		if (check_var_temp(parsed))
		{
			free(new_input);
			free_array(parsed);
			continue ;
		}
		if (!new_input || ft_strncmp(parsed[0], "exit", 4) == 0)
		{
			free(new_input);
			ft_exit(parsed, params);
			break ;
		}
		//print_argv(parsed);
		//printf("%s\n", new_input);
		params->command = init_command(parsed);
		free_array(parsed);
		free(new_input);
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
	ignore_leaks_readline();
	add_old_history();
	run_minishell(params);
	cleanup_and_exit(params, 0);
	return (0);
}
