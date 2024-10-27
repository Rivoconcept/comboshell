/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:31:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/18 10:04:39 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

void print_prompt()
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("minishell: %s$ ", cwd);
    } else {
        perror("getcwd() error");
    }
}