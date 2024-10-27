/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 14:59:29 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rivo.h"

int check_error_newline(char *s)
{
    int i;
    char *base[] = {">", "<", ">>", "<<", "<>", "<<<", "$", "<echo<",
        ">>echo>>", "cat >>", "cat <<", NULL};

    i = 0;
    while(base[i] != NULL)
    {
        if (!ft_strcmp(s, base[i]) && ft_strlen(s) == ft_strlen(base[i]))
            return (1);
        i++;
    }
    return (0);
}

int check_behavior(char *s)
{
    if (check_input(s, "\t\n\v\f\r ") || !ft_strcmp(s, ":") || !ft_strcmp(s, "!"))
        return (1);
    if (check_str(s, "<>", "<> "))
        return (printf("bash: syntax error near unexpected token '<>'\n"), 1);
    if (check_str(s, "><<<", "<> ") || check_str(s, " <<<", "<> ")
        || !ft_strcmp(s, "<<<<<<"))
        return (printf("bash: syntax error near unexpected token '<<<'\n"), 1);
    if (check_str(s, " <<", "<> ") || check_str(s, "><<", "<> ")
        || !ft_strcmp(s, "<<<<<"))
        return (printf("bash: syntax error near unexpected token '<<'\n"), 1);
    if (check_str(s, " <", "<> ") || check_str(s, "><", "<> ")
        || !ft_strcmp(s, "<<<<"))
        return (printf("bash: syntax error near unexpected token '<'\n"), 1);
    if (check_str(s, " >>", "<> ") || !ft_strcmp(s, "<>>>")
        || !ft_strcmp(s, ">>>>"))
        return (printf("bash: syntax error near unexpected token '>>'\n"), 1);
    if (ft_strcmp(s, "<>>") == 0|| check_str(s, " >", "<> ")
        || !ft_strcmp(s, ">>>"))
        return (printf("bash: syntax error near unexpected token '>'\n"), 1);
    if (check_error_newline(s))
        return (printf("bash: syntax error near unexpected token 'newline'\n"), 1);
    if (check_input(s, "/. ") || !ft_strcmp(s, "$HOME"))
        return (printf("bash: %s: Is a directory\n", s), 1);
    if (!ft_strcmp(s, "||") 
        || (check_input(s, "| <>") && check_str(s, "||", "<> |")))
        return (printf("bash: syntax error near unexpected token '||'\n"), 1);
    if (!ft_strcmp(s, "|") || (check_input(s, "| <>") && check_str(s, "|", "<> |")))
        return (printf("bash: syntax error near unexpected token '|'\n"), 1);
    if (!ft_strcmp(s, "&&"))
        return (printf("bash: syntax error near unexpected token '&&'\n"), 1);
    if (!ft_strcmp(s, ";;"))
        return (printf("bash: syntax error near unexpected token ';;'\n"), 1);

    return (0);
}