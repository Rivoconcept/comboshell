/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_handle_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 08:00:05 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/27 17:49:32 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_here(char *content, int num_cmd)
{
	char	*file;
	int		fd;
	char	*ext;

	ext = ft_itoa(num_cmd);
	file = ft_strjoin("/home/rrakoton/here/josia", ext);
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

static int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

static char *trim_space(char *str) {
    char *end;

    while (ft_isspace(*str))
        str = str + 1;
    end = str + strlen(str) - 1;
    while (end > str && ft_isspace(*end))
        end = end - 1;
    *(end+1) = '\0';
    return str;
}

int	handle_here(char *delimiter, char **here_content,
		t_here_data *here_data, t_params *params)
{
	char	*line;
	size_t	len;

	len = 0;
	*here_content = malloc(1);
	if (!*here_content)
		return (1);
	**here_content = '\0';
	
	while (1)
	{
		signal_handlers(SIGINT);
		line = readline("> ");
		if (line == NULL)
		{
			write_here(*here_content, here_data->j);
			free(line);
			printf("warning: here-document\n");
			break ;
		}
		if(g_sig_num == SIGINT)
		{
			g_sig_num = 0;
			dup2(params->fd_in, STDIN_FILENO);
			return (1);
		}
		delimiter = trim_space(delimiter);
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
	return(0);
}
