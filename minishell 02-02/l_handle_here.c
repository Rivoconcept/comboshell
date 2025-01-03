/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_handle_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 08:00:05 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/01 22:42:25 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_here(char *content, int num_cmd)
{
	char	*file;
	int		fd;
	char	*ext;

	ext = ft_itoa(num_cmd);
	file = ft_strjoin(ROOT, ext);
	free(ext);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
	{
		write(fd, content, ft_strlen(content));
		if (fd >= 0)
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

static int	get_here_input(char **line, char **here_content,
		t_here_data *here_data)
{
	signal_handlers(SIGINT);
	*line = readline("> ");
	if (*line == NULL)
	{
		write_here(*here_content, here_data->j);
		free(*line);
		perror_msg(": warning: here-document\n", NULL);
		return (1);
	}
	return (0);
}

static int	initialize_here_content(char **here_content, size_t *len)
{
	*len = 0;
	*here_content = malloc(1);
	if (!*here_content)
		return (1);
	**here_content = '\0';
	return (0);
}

int	handle_here(char *delimiter, char **here_content, t_here_data *here_data,
		t_params *params)
{
	char	*line;
	size_t	len;

	if (initialize_here_content(here_content, &len))
		return (1);
	while (1)
	{
		if (get_here_input(&line, here_content, here_data))
			break ;
		if (handle_sigint(params))
			return (1);
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
	return (0);
}
