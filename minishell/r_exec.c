/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 18:03:22 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_pipe_fd(int ***fd, int pipe_count)
{
	int i = 0;
	while(i < pipe_count){
		if ((*fd)[i]) {
			close((*fd)[i][0]);
			close((*fd)[i][1]);
			free((*fd)[i]);
		}
		i++;
	}
	free(*fd);
	*fd = NULL;
}

int put_nbr_pipes(t_cmd *command)
{
	int count = 0;
	while (command != NULL) {
		if (!ft_strcmp(command->cmd[0], "|"))
			count++;
		command = command->next;
	}
	return count;
}

void init_pipe_fd(int ***fd, t_params *params)
{
	int i = 0;
	int pipe_count = put_nbr_pipes(params->command);
	*fd = malloc(sizeof(int *) * pipe_count);
	if (!*fd) {
		perror("malloc");
		cleanup_and_exit(params, EXIT_FAILURE);
	}
	while(i < pipe_count){
		(*fd)[i] = malloc(sizeof(int) * 2);
		if (!(*fd)[i]) {
			perror("malloc");
			clean_pipe_fd(fd, i);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
		if (pipe((*fd)[i]) == -1) {
			perror("pipe");
			clean_pipe_fd(fd, i);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
		i++;
	}
}

int setup_pipe(int **fd, t_cmd *current, int i)
{
	if (current->previous && !ft_strcmp(current->previous->cmd[0], "|")) {
		if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close(fd[i - 1][0]);
	}
	if (current->next && !ft_strcmp(current->next->cmd[0], "|")) {
		if (dup2(fd[i][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close(fd[i][1]);
	}
	return 0;
}

int ft_get_pid_nbr(t_params *params)
{
	int nbr;
	t_cmd *current;

	current = params->command;
	nbr = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->cmd[0], "|") == 0)
		{
			current = current->next;
			continue ;
		}
		current = current->next;
		nbr++;
	}
	return (nbr);
}

int	ft_check_continue(t_params *params, t_cmd **current, int *rank_cmd)
{
	if (!ft_strcmp((*current)->cmd[0], "|"))
	{
		(*current) = (*current)->next;
		(*rank_cmd)++;
		return (1);
	}
	if (isbuiltins((*current)->cmd[0]) && (*current)->next == NULL)
	{
		input_r((*current), *rank_cmd);
		output((*current));
		params->last_exit_code = run_builtins((*current)->cmd, params);
		dup2(params->fd_in, STDIN_FILENO);
		dup2(params->fd_out, STDOUT_FILENO);
		(*current) = (*current)->next;
		return (1);
	}
	return (0);
}

void ft_handle_child(t_params *params, pid_t *pid_tab)
{
	int fd[2];
	t_cmd *current;
	int tab;
	int rank_cmd;

	current = params->command;
	tab = 0;
	rank_cmd = 0;
	while (current != NULL)
	{
		if (ft_check_continue(params, &current, &rank_cmd) == 1)
			continue ;
		if (pipe(fd) == -1)
		{
			perror("pipe");
			free(pid_tab);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
		pid_tab[tab] = fork();
		if ( pid_tab[tab] == -1)
		{
			perror("fork");
			free(pid_tab);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
		if (pid_tab[tab] == 0) 
		{
			if(current->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			signal(SIGQUIT, SIG_DFL);
			input_r(current, rank_cmd);
			output(current);
			if (isbuiltins(current->cmd[0]))
			{
				params->last_exit_code = run_builtins(current->cmd, params);

				free_list_cmd(params->command);
				 close(fd[0]);
				cleanup_and_exit(params, params->last_exit_code);
			}
			close(fd[0]);
			if (execve(current->cmd[0], current->cmd, params->envp) == -1) {
				perror("execve");
				free_list_cmd(params->command);
				cleanup_and_exit(params, 127);
			}
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		 tab++;
		rank_cmd++;
		current = current->next;
	}
	
}

void exec_cmd(t_params *params)
{
	t_cmd *current;
	pid_t *pid_tab;
	int status;
	int tab;

	current = params->command;
	params->fd_in = dup(STDIN_FILENO);
	params->fd_out = dup(STDOUT_FILENO);
	if (params->envp)
		free_array(params->envp);
	params->envp = put_envp(params);
	pid_tab = malloc(sizeof(pid_t) * ft_get_pid_nbr(params));
	tab = 0;
	ft_handle_child(params, pid_tab);
	while (current != NULL)
	{
		if (ft_strcmp(current->cmd[0], "|") == 0)
		{
			current = current->next;
			continue ;
		}
		waitpid(pid_tab[tab], &status, 0);
		if (WIFEXITED(status))
			params->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status)) {
			if (WTERMSIG(status) == SIGQUIT)
				printf("Quit (core dumped)\n");
			else if (WTERMSIG(status) == SIGINT)
				params->last_exit_code = 128 + WTERMSIG(status);
			else
				params->last_exit_code = 128 + WTERMSIG(status);
		}
		current = current->next;
		tab++;
	}
	free(pid_tab);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
	close(params->fd_in);
	close(params->fd_out);
}
