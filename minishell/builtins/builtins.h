/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:55:48 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/19 21:33:57 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// # include "../libft/libft.h"
// # include "../utils/utils.h"
# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main(int argc, char **argv);
int main(int argc, char **argv);
int	ft_print_echo(char *input, int fd);
int check_dash_n(char *str);
// int	ft_echo(char **argv, int *count, int flag[2], int fd);
int ft_echo(char **argv, int flag[2], int fd);

#endif
