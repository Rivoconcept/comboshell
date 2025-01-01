/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:10:32 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/30 21:42:20 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (size > ft_strlen((char *)s))
		len = ft_strlen((char *)s);
	else
		len = size;
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = ((char *)s)[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	reset_cmd_flags(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		current->flag_less = 0;
		current->here = -1;
		current->rank_here = 0;
		current->less = NULL;
		current->rank_less = 0;
		current->great = NULL;
		current->rank_great = 0;
		current->dgreat = NULL;
		current->rank_dgreat = 0;
		current = current->next;
	}
}
