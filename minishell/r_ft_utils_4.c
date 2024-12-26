/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/26 14:11:49 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isoperator(char *input)
{
	int		i;
	char	*op[11];

	if (!input)
		return (0);
	op[0] = ">";
	op[1] = ">>";
	op[2] = "<";
	op[3] = "<<";
	op[4] = "&";
	op[5] = "&&";
	op[6] = "|";
	op[7] = "||";
	op[8] = ";";
	op[9] = ";;";
	op[10] = NULL;
	i = 0;
	while (op[i] != NULL)
	{
		if (!ft_strncmp(input, op[i], ft_strlen(op[i])))
			return (1);
		i++;
	}
	return (0);
}

int	check_path(const char *path)
{
	struct stat	statbuf;
	char		*last_slash;
	char		parent_path[1024];

	if (path[0] == '\0' || !path || path == NULL)
		return (0);
	ft_strlcpy(parent_path, path, sizeof(parent_path) - 1);
	parent_path[sizeof(parent_path) - 1] = '\0';
	last_slash = ft_strrchr(parent_path, '/');
	if (path[0] != '/' && access(path, X_OK) != 0)
		return (printf("minishell: %s: command not found\n", path), 127);
	if (last_slash && last_slash != parent_path)
	{
		*last_slash = '\0';
		if (stat(parent_path, &statbuf) != 0)
			return (perror(path), 127);
		if (!S_ISDIR(statbuf.st_mode))
			return (printf("minishell: %s: Not a directory\n", path), 126);
	}
	if (stat(path, &statbuf) != 0)
		return (printf("minishell: %s: No such file or directory\n", path),
			127);
	if (S_ISDIR(statbuf.st_mode))
		return (printf("%s: is a directory\n", path), 126);
	return (0);
}

int	pre_test(char *arg, t_params *params)
{
	if (arg && ft_strncmp(arg, "|", 2) == 0)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", arg);
		params->last_exit_code = 2;
		return (1);
	}
	if (arg && ft_strncmp(arg, "||", 3) == 0)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", arg);
		params->last_exit_code = 2;
		return (1);
	}
	return (0);
}

void check_cmd_not_found(t_params *params, char *cmd, int *i)
{
	int	status;

	status = 0;
	if (!isbuiltins(cmd))
	{
		status = check_path(cmd);
		if (status)
		{
			params->last_exit_code = status;
			(*i)++;
		}
	}

}

int check_errors(t_params *params)
{
    int		i;
	t_cmd	*current;

    i = 0;
	current = params->command;
	if (pre_test(current->cmd[0], params))
		return (1);
    while(current != NULL)
    {
		if (ft_strncmp(current->cmd[0], "|", 1) == 0 &&  !ft_strncmp(current->cmd[0], "echo", 5)
			&& current->previous->cmd && current->next->cmd 
			&& (ft_strcmp(current->previous->cmd[0], "|") != 0
			|| ft_strcmp(current->next->cmd[0], "|") != 0))
        {
            current = current->next;
            continue ;
        }
		if (pass_errors_test(current->cmd[0], params))
			return (1);
		check_cmd_not_found(params, current->cmd[0], &i);
        current = current->next;
    }
	return (i);
}

void	*safe_malloc(size_t bytes, char *errors)
{
	void	*res;

	res = malloc(bytes);
	if (res == NULL)
		exit_error(errors);
	return (res);
}
