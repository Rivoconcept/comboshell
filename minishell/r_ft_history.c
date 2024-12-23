/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:50:43 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 15:59:55 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ignore_leaks_readline(void)
{
    int fd;
    const char *content = 
        "{\n"
        "    leak readline\n"
        "    Memcheck:Leak\n"
        "    ...\n"
        "    fun:readline\n"
        "}\n"
        "{\n"
        "    leak add_history\n"
        "    Memcheck:Leak\n"
        "    ...\n"
        "    fun:add_history\n"
        "}\n";

    fd = open(READLINE_IGN, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
	{
        perror("Error opening .readline.ign file");
        return 1;
    }

    if (write(fd, content, strlen(content)) == -1)
	{
        perror("Error writing to .readline.ign file");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}


void	add_old_history(void)
{
	int		fd;
	char	*input;

	fd = open(HISTORY_FILE, O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error opening history file");
		return ;
	}
	input = get_next_line(fd);
	while (input)
	{
		input[strlen(input) - 1] = '\0';
		add_history(input);
		free(input);
		input = get_next_line(fd);
	}
	close(fd);
}

void	push_history(const char *input)
{
	int	fd;

	fd = open(HISTORY_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error opening history file");
		return ;
	}
	write(fd, input, strlen(input));
	write(fd, "\n", 1);
	close(fd);
}
