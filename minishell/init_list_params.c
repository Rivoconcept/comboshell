/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:21:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/23 17:12:37 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	put_operators(t_params **params, char **argv, int *index)
{
	char	**operator;

	operator= malloc(sizeof(char *) * 2);
	if (!operator)
		return ;
	operator[0] = strdup(argv[*index]);
	operator[1] = NULL;
	append_params(params, operator);
}

int	put_argv_cmd(t_params **params, char **argv, int *index)
{
	int		j;
	int		size;
	char	**argv_list;

	j = 0;
	size = ft_argvlen(argv, index);
	argv_list = malloc(sizeof(char *) * (size + 1));
	if (!argv_list)
		return (0);
	while (j < size)
	{
		argv_list[j] = strdup(argv[*index + j]);
		j++;
	}
	argv_list[j] = NULL;
	append_params(params, argv_list);
	return (size);
}

t_params	*parse_command_into_params(char **argv, char const *input)
{
	int			i;
	t_params	*params;

	if (!input)
		return (NULL);
	i = 0;
	params = NULL;
	while (argv[i] != NULL)
	{
		if (is_operator(argv[i]))
			put_operators(&params, argv, &i);
		else
			i += put_argv_cmd(&params, argv, &i) - 1;
		i++;
	}
	return (params);
}

/*int main(void)
{
	char *input = "ls -la | grep \"test\" | wc -l >> text.txt";
	t_params *params_list = parse_command_into_params(input);

	// Parcourir la liste pour afficher chaque sous-commande/paramètre
	t_params *temp = params_list;
	while (temp)
	{
		for (int i = 0; temp->str[i]; i++)
		{
			printf("%s ", temp->str[i]);
		}
		printf("\n");
		temp = temp->next;
	}
	free_list_params(params_list);
	return (0);
}*/