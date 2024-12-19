/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:38:41 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/18 14:37:49 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_infile(char **argv)
{
    int i;
	i = 0;
    while (argv[i] != NULL)
    {
        if (ft_strcmp(argv[i], "<") == 0 && access(argv[i + 1], F_OK | W_OK) != 0)
			return (0);
        i++;
    }
	return (1);
}