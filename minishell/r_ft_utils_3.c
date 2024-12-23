/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/22 20:48:03 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltins(char *command)
{
	int		i;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};

	i = 0;
	while (builtins[i] != NULL)
	{
		if (!ft_strcmp(command, builtins[i]) && ft_strlen(command) == ft_strlen(builtins[i]))
			return (1);
        i++;
	}
	return (0);
}

int count_cmd(t_params *params)
{
    int     count;
    t_cmd   *current;

    count  = 0;
    current = params->command;
    while(current != NULL)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int putchar_count(const char *src, char c)
{
    size_t i;
    size_t count;

    i = 0;
    count = 0;
    if (!*src)
        return (0);
    while (src[i] != '\0')
    {
        if (src[i] == c)
            count++;
        i++;
    }
    return (count);
}