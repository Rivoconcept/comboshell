/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:24:53 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/17 20:53:38 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main(int argc, char **argv)
{
    char *cwd;

    if (argc != 1)
        return (0);
    (void)argv;
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        return (perror("Error on getcwd"), 1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}