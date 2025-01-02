/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdl_ignore_leaks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:01:50 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 12:09:35 by rhanitra         ###   ########.fr       */
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


rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ fghjkl
fghjkl: command not found
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ echo $?
127
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ /ls
bash: /ls: No such file or directory
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ echo $?
127
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ /bin/ls/hfj
bash: /bin/ls/hfj: Not a directory
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ echo $?
126
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ touch a
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ ./a
bash: ./a: Permission denied
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ echo $?
126
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ $HOME
bash: /home/rrakoton: Is a directory
rrakoton@c1r9s3:~/Downloads/comboshell-main/minishell$ echo $?
126
