/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:14:30 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/11 22:14:30 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quote(char *str)
{
    int dquote;
    int squote;
    int i;

    dquote = 0;
    squote = 0;
    i = 0;
    while(str[i])
    {
        if(dquote == 0 && str[i] == '"' && squote == 0)
            dquote = 1;
        else if (dquote == 1 && str[i - 1] != '\\' && str[i] == '"' && squote == 0)
            dquote = 0;
        else if(dquote == 1 && str[i] == '\'' && squote == 0)
            squote = 0;
        else if (squote == 0 && str[i] == '\'' && dquote == 0)
            squote = 1;
        else if(squote == 1  && str[i - 1] != '\\' && str[i] == '\'' && dquote == 0)
            squote = 0;
        else if(squote == 1 && str[i] == '"' && dquote == 0)
            dquote = 0;
        i++;
    }
    return (dquote || squote);
}

int dquote_length(char *str, int pos, char quote)
{
    while(str[++pos])
    {
        if (str[pos - 1] != '\\' && str[pos] == quote)
           return (pos + 1);
    }
    return (-1);
}

/*if(check_quote(input) == 1)
                ft_putendl_fd("Erreur : guillemets non fermés !", 2);*/