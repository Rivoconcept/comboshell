/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 18:12:03 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_pipe_fd(int ***fd, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if ((*fd)[i])
		{
			close((*fd)[i][0]);
			close((*fd)[i][1]);
			free((*fd)[i]);
		}
		i++;
	}
	free(*fd);
	*fd = NULL;
}

int	put_nbr_pipes(t_cmd *command)
{
	int	count;

	count = 0;
	while (command != NULL)
	{
		if (!ft_strcmp(command->cmd[0], "|"))
			count++;
		command = command->next;
	}
	return (count);
}
void cleanup_error_malloc_fd(t_params *params)
{
	perror("malloc");
	cleanup_and_exit(params, EXIT_FAILURE);
}
void	init_pipe_fd(int ***fd, t_params *params)
{
	int	i;
	int	pipe_count;

	i = -1;
	pipe_count = put_nbr_pipes(params->command);
	*fd = malloc(sizeof(int *) * pipe_count);
	if (!*fd)
		cleanup_error_malloc_fd(params);
	while (++i < pipe_count)
	{
		(*fd)[i] = malloc(sizeof(int) * 2);
		if (!(*fd)[i])
		{
			perror("malloc");
			clean_pipe_fd(fd, i);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
		if (pipe((*fd)[i]) == -1)
		{
			perror("pipe");
			clean_pipe_fd(fd, i);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
	}
}

int	setup_pipe(int **fd, t_cmd *current, int i)
{
	if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
	{
		if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close(fd[i - 1][0]);
	}
	if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
	{
		if (dup2(fd[i][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close(fd[i][1]);
	}
	return (0);
}

int	ft_get_pid_nbr(t_params *params)
{
	int		nbr;
	t_cmd	*current;

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

void	exec_builtins(t_params *params, t_cmd *current)
{
	input_r(current, params->rank_cmd, params, 0);
	output(current, params);
	params->last_exit_code = run_builtins(current->cmd, params);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
}

int	ft_check_continue(t_params *params, t_cmd **current)
{
	if (!ft_strcmp((*current)->cmd[0], "|"))
	{
		(*current) = (*current)->next;
		params->rank_cmd++;
		return (1);
	}
	return (0);
}

void	check_fork_error(t_params *params, t_cmd *current, int tab, int fd[2])
{
	if (params->pid_tab[tab] == -1)
	{
		perror("fork");
		if (params->prev_pipe_read != -1)
			close(params->prev_pipe_read);
		if (current->next)
		{
			close(fd[0]);
			close(fd[1]);
		}
		cleanup_and_exit(params, EXIT_FAILURE);
	}
}

void	exec_child_builtins(t_params *params, t_cmd *current)
{
	if (isbuiltins(current->cmd[0]))
	{
		run_builtins(current->cmd, params);
		cleanup_and_exit(params, params->last_exit_code);
	}
}
void	exec_child(t_params *params, t_cmd *current, int fd[2])
{
	close(params->fd_in);
	close(params->fd_out);
	if (params->prev_pipe_read != -1)
	{
		dup2(params->prev_pipe_read, STDIN_FILENO);
		close(params->prev_pipe_read);
	}
	if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	signal(SIGQUIT, SIG_DFL);
	input_r(current, params->rank_cmd, params, 1);
	output(current, params);
	exec_child_builtins(params, current);
	if (execve(current->cmd[0], current->cmd, params->envp) == -1)
	{
		perror("execve");
		free_list_cmd(params->command);
		cleanup_and_exit(params, 127);
	}
}

void	exec_child_process(t_params *params, t_cmd *current, int tab, int fd[2])
{
	if (params->pid_tab[tab] == 0)
	{
		exec_child(params, current, fd);
	}
	else
	{
		if (params->prev_pipe_read != -1)
			close(params->prev_pipe_read);
		if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
		{
			close(fd[1]);
			params->prev_pipe_read = fd[0];
		}
		else
		{
			params->prev_pipe_read = -1;
		}
	}
}

void	check_pipe_error(t_params *params)
{
	perror("pipe");
	if (params->prev_pipe_read != -1)
		close(params->prev_pipe_read);
	free(params->pid_tab);
	cleanup_and_exit(params, EXIT_FAILURE);
}

void	ft_handle_child(t_params *params)
{
	int		fd[2];
	t_cmd	*current;
	int		tab;

	current = params->command;
	tab = 0;
	if (current->cmd[0] && isbuiltins(current->cmd[0]) && current->next == NULL)
	{
		exec_builtins(params, current);
		current = current->next;
	}
	else
	{
		while (current != NULL)
		{
			if (ft_check_continue(params, &current) == 1)
				continue ;
			if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
			{
				if (pipe(fd) == -1)
					check_pipe_error(params);
			}
			params->pid_tab[tab] = fork();
			check_fork_error(params, current, tab, fd);
			exec_child_process(params, current, tab, fd);
			tab++;
			params->rank_cmd++;
			current = current->next;
			if (current && !ft_strcmp(current->cmd[0], "|"))
			{
				params->rank_cmd++;
				current = current->next;
			}
		}
	}
}

void	wait_pid(t_params *params, t_cmd *current, int status)
{
	int	tab;

	tab = 0;
	while (current != NULL)
	{
		if (!ft_strcmp(current->cmd[0], "|"))
		{
			current = current->next;
			continue ;
		}
		waitpid(params->pid_tab[tab], &status, 0);
		if (WIFEXITED(status))
			params->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
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
}

void	exec_cmd(t_params *params)
{
	int		status;

	status = 0;
	if (params->envp)
		free_array(params->envp);
	params->envp = put_envp(params);
	params->pid_tab = malloc(sizeof(pid_t) * ft_get_pid_nbr(params));
	if (!params->pid_tab)
	{
		perror("malloc");
		cleanup_and_exit(params, EXIT_FAILURE);
	}
	ft_memset(params->pid_tab, 0, sizeof(pid_t) * ft_get_pid_nbr(params));
	ft_handle_child(params);
	if (!(isbuiltins(params->command->cmd[0]) && params->command->next == NULL))
		wait_pid(params, params->command, status);
	free(params->pid_tab);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
}
