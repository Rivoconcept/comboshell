/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:50 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 18:41:44 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
// consume SPACES
static void parse_space(char *itr, int *i){
    if(peek(itr, i) ==  32 || peek(itr, i) ==  9)
    {
        scanner_next(itr, i);
        parse_space(itr, i);
    }
}*/

// STR_NODE    ::= CMD_TOKEN
static s_node* parse_str(char *itr, int *i)
{
    char *str;
    size_t j;
   // int start;

   // start = *i;
    s_token next = scanner_next(itr, i);
    j = 0;
    str = (char *)malloc(sizeof(char) * (next.location.length) + 1);
    if(!str)
        return (NULL);
    ft_bzero(str, next.location.length + 1);
    while(j <  next.location.length){
        str[j] = next.location.start[j];
        j++;
    }
    return strnode_new(str);
}
/*

// CHAR_NODE    ::= COL_TOKEN
static s_node* parse_char(char *itr, int *i)
{
    s_token next = scanner_next(itr, i);
    return charnode_new(next.location.start[0]);
}*/

s_node *parse(char *itr, int *i) {
    s_node *left = NULL;
    s_node *right = NULL;
    s_token next;

    left = parse_str(itr, i);

    while (scanner_has_next(itr, i)) {
        next = scanner_peek(itr, i);
        if (next.type == PIPE_TOKEN) {
            scanner_next(itr, i);
            right = parse_str(itr, i);
            if (!right) {
                return errornode_new("Expected a command after |");
            }
            left = pairnode_new(left, right);
        } else {
            break;
        }
    }

    return left;
}
