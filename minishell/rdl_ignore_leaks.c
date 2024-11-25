/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl_ignore_leaks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:01:50 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/23 12:44:05 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// https://www.youtube.com/watch?v=CEEmw_vXCbw
// https://www.youtube.com/watch?v=H61EC4CZnx8
// https://www.youtube.com/watch?v=6b6kE4jC2UY
// https://www.youtube.com/watch?v=4xN6pdUXj14

/*{
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}*/


// https://www.youtube.com/watch?v=1z6EUUl11qI
/*
https://www.youtube.com/watch?v=y_i7GHo8WFk

void print_argv(char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }

}https://www.youtube.com/watch?v=_vDWSRusNKI
https://www.rvq.fr/pannes/lisseur.php

valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell


*/