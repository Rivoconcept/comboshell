/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/03 17:36:23 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_pipe(char *s)
{
	if (!s || s == NULL)
		return (0);
	return (s[0] == '|' && s[1] == '\0');
}

int isoperator(char *s)
{
	if (!s || s == NULL)
		return (0);
	return ((is_operator(s[0]) && s[1] == '\0') \
		|| (is_operator(s[0]) && s[1] == s[0] && s[2] == '\0'));
}

int	count_cmd(t_cmd *command)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = command;
	while (current != NULL)
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

int	putchar_count(const char *src, char c)
{
	size_t	i;
	size_t	count;

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
