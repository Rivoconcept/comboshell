/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:36:27 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 11:36:27 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i - 1] == c && s[i] != c
				&& s[i] != '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_word_len(char const *s, int start, char c)
{
	int	count;

	count = 0;
	while (s[start] != '\0')
	{
		if (s[start] != c && s[start] != '\0')
			count++;
		else
			break ;
		start++;
	}
	return (count);
}

static void	ft_initialize(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	**ft_split(char *s, char c)
{
	char	**new;
	int		i;
	int		j;

	ft_initialize(&i, &j);
	new = (char **)malloc((ft_word(s, c) + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			new[j] = ft_subfirst(s, i, ft_word_len(s, i, c));
			if (!(new[j]))
				return (ft_free(new, j));
			j++;
			i += ft_word_len(s, i, c) - 1;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}