/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:23:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/27 22:18:43 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	clean_cmd(t_cmd **cmd, char ***temp)
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
}*/

void free_command(t_cmd *command)
{
    int i;

    i = 0;
	if (!command)
        return;
    if (command->cmd)
    {
        while (command->cmd[i])
        {
            free(command->cmd[i]);
            i++;
        }
        free(command->cmd);
    }
    free(command);
}

t_cmd *remove_element_cmd(t_cmd *head, t_cmd *to_remove)
{
    t_cmd *current = head;
    t_cmd *prev = NULL;

    if (!head || !to_remove)
        return head;
    if (head == to_remove)
    {
        head = head->next;
        free_command(to_remove);
        return head;
    }
    while (current && current != to_remove)
    {
        prev = current;
        current = current->next;
    }
    if (current == to_remove)
    {
        prev->next = current->next;
        free_command(current);
    }
    return head;
}
