/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 14:59:19 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rivo.h"

int	put_new_size(char *input, char *operators)
{
	int	i;
	int	j;
	int	new_size;

	i = -1;
	new_size = 0;
	while (input[++i] != '\0')
	{
		j = -1;
		while (operators[++j] != '\0')
		{
			if (input[i] == operators[j])
			{
				if (input[i - 1] != ' ' && input[i - 1] != operators[j]
					&& i != 0)
					new_size++;
				if (input[i + 1] != ' ' && input[i + 1] != operators[j]
					&& input[i] != '\0')
					new_size++;
			}
		}
	}
	return (ft_strlen(input) + new_size);
}

void	add_spaces(char *new_str, char *input, char c, int var[3])
{
	int	i;

	i = 0;
	if (input[(var[0]) - 1] != 32 && var[1] > 0 && new_str[var[1] - 1] != ' ')
		new_str[(var[1])++] = ' ';
	while (input[(var[0]) + i] == c)
	{
		new_str[(var[1])++] = c;
		i++;
	}
	(var[0]) += i;
	if (input[(var[0])] != 32 && input[(var[0])] != '\0')
		new_str[(var[1])++] = ' ';
}

char	*format_input(char *input, char *operators)
{
	int		var[3] = {0, 0, 0};
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (put_new_size(input, operators)
				+ 2));
	if (!new_str)
		return (NULL);
	while (input[(var[0])] != '\0')
	{
		var[2] = -1;
		while (operators[++(var[2])] != '\0')
		{
			if (input[(var[0])] == operators[(var[2])])
			{
				add_spaces(new_str, input, operators[(var[2])], var);
				break ;
			}
		}
		new_str[(var[1])++] = input[(var[0])++];
	}
	new_str[(var[1])] = '\0';
	return (new_str);
}