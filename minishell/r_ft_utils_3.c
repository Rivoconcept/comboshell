/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 12:59:19 by rhanitra         ###   ########.fr       */
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
    current = params->cmd;
    while(current != NULL)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t 			n;
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	n = ft_strlen((char *)s2);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n > 0)
	{
		while (str1[i] == str2[i] && str1[i] != '\0'
			&& str2[i] != '\0' && 1 < n)
		{
			i++;
			n--;
		}
		return (str1[i] - str2[i]);
	}
	else
		return (0);
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