/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_handle_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 08:00:05 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/24 14:53:11 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_here(char *content, int num_cmd)
{
	char	*file;
	int		fd;
	char	*ext;

	ext = ft_itoa(num_cmd);
	file = ft_strjoin("/tmp/josia", ext);
	free(ext);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		write(fd, content, ft_strlen(content));
		close(fd);
	}
	free(file);
}

static void	append_line_to_content(char **here_content, char *line, size_t *len)
{
	size_t	new_len;
	char	*temp;

	new_len = *len + ft_strlen(line) + 1;
	temp = ft_realloc(*here_content, *len, new_len + 1);
	if (!temp)
	{
		free(*here_content);
		free(line);
		return ;
	}
	*here_content = temp;
	ft_memcpy(*here_content + *len, line, ft_strlen(line));
	*len += ft_strlen(line);
	(*here_content)[*len] = '\n';
	(*len)++;
	(*here_content)[*len] = '\0';
	free(line);
}

void	handle_here(char *delimiter, char **here_content,
		t_here_data *here_data, t_params *params)
{
	char	*line;
	size_t	len;

	len = 0;
	*here_content = malloc(1);
	if (!*here_content)
		return ;
	**here_content = '\0';
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if ((ft_strcmp(line, delimiter) == 0) || ((ft_strcmp(delimiter,
						"\"\"") == 0 || ft_strcmp(delimiter, "''") == 0)
				&& ft_strlen(line) == 0))
		{
			write_here(*here_content, here_data->j);
			free(line);
			break ;
		}
		if (here_data->quote == 0)
			line = expand_variable_in_input(line, params);
		append_line_to_content(here_content, line, &len);
	}
}
