/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:21:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 14:59:17 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rivo.h"

int	is_operator(char *str)
{
	return (!ft_strcmp(str, "|") || !ft_strcmp(str, ">") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">>") || !ft_strcmp(str, "&&") 
		|| !ft_strcmp(str, "||") || !ft_strcmp(str, ";"));
}

t_params	*create_params(char **argv)
{
	t_params	*new_params;

	new_params = malloc(sizeof(t_params));
	if (!new_params)
		return (NULL);
	new_params->str = argv;
	new_params->next = NULL;
	return (new_params);
}

void	append_params(t_params **params_list, char **argv)
{
	t_params	*new_params;
	t_params	*temp;

	new_params = create_params(argv);
	if (!new_params)
		return ;
	if (*params_list == NULL)
		*params_list = new_params;
	else
	{
		temp = *params_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_params;
	}
}

void	free_list_params(t_params *params)
{
	t_params	*temp;
	t_params	*current;

	if (!params)
		return ;
	temp = NULL;
	current = params;
	while (current != NULL)
	{
		temp = current->next;
		free_array(current->str);
		free(current);
		current = temp;
	}
	params = NULL;
}

int	ft_argvlen(char **argv, int *index)
{
	int	len;

	len = 0;
	while (argv[*index + len] && !is_operator(argv[*index + len]))
		len++;
	return (len);
}
