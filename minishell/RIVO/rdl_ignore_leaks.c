/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl_ignore_leaks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:01:50 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 16:52:16 by rhanitra         ###   ########.fr       */
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
https://www.youtube.com/watch?v=_jsN9tCegy0

void print_argv(char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }

}

    valgrind --track-origins=yes --show-leak-kinds=all --leak-check=full ./minishell
    """''"e"c'h'o ""''-n'n's '-l's''"comment 'faire' des '$HO''ME'" '"$HOME" est un $HOME qui va "$HOME"'''""'pe''"y"' "'$HOME' est un "$HOME" qui va '$HOME'"||""''w'c' -l > ""''test.txt"
*/