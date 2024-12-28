/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:23:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 11:17:33 by rhanitra         ###   ########.fr       */
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

    if (!command)
        return;

    if (command->cmd)
    {
        i = 0;
        while (command->cmd[i])
        {
            free(command->cmd[i]);
            command->cmd[i] = NULL; // Remet le pointeur à NULL après libération
            i++;
        }
        free(command->cmd);
        command->cmd = NULL;         // Remet le pointeur principal à NULL
    }

    free(command);
    command = NULL;                  // Remet le pointeur principal à NULL
}


t_cmd *remove_element_cmd(t_cmd *head, t_cmd *to_remove)
{
    t_cmd *current = head;
    t_cmd *prev = NULL;

    if (!head || !to_remove)
        return head;

    // Si l'élément à supprimer est la tête
    if (head == to_remove)
    {
        head = head->next;           // Mise à jour de la tête
        free_command(to_remove);     // Libération de l'élément
        to_remove = NULL;            // Mise à NULL
        return head;
    }

    // Recherche de l'élément à supprimer
    while (current && current != to_remove)
    {
        prev = current;
        current = current->next;
    }

    // Si l'élément a été trouvé
    if (current == to_remove)
    {
        prev->next = current->next;  // Mise à jour du lien
        free_command(current);       // Libération de l'élément
        current = NULL;              // Mise à NULL
    }

    return head;
}
int delete_cmd_null(t_params *params)
{
    t_cmd *current;
    t_cmd *next;

    current = params->command;
    while (current != NULL)
    {
        next = current->next;
        if ((current->cmd && current->cmd[0] && ft_strncmp(current->cmd[0], "\0", 1) == 0) &&
            next && next->cmd && ft_strcmp(next->cmd[0], "|") == 0)
        {
            params->command = remove_element_cmd(params->command, current);
            params->command = remove_element_cmd(params->command, next);
            current = params->command;
            continue;
        }
        current = next;
    }
    return (0);
}





