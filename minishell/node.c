/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:07:13 by rrakoton          #+#    #+#             */
/*   Updated: 2024/09/23 11:07:13 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_node *strnode_new(char *c)
{
    s_node* node = guard(malloc(sizeof(s_node)), __FILE__, __LINE__);
    node->type = STR_NODE;
    node->data.str = c;
    return (node);
}

s_node *charnode_new(char c)
{
    s_node* node = guard(malloc(sizeof(s_node)), __FILE__, __LINE__);
    node->type = CHAR_NODE;
    node->data.value = c;
    return (node);
}

s_node *pairnode_new(s_node *left, s_node *right)
{
    s_node* node = guard(malloc(sizeof(s_node)), __FILE__, __LINE__);
    node->type = PAIR_NODE;
    node->data.pair.left = left;
    node->data.pair.right = right;
    return (node);
}

s_node *errornode_new(char *msg)
{
    s_node* node = guard(malloc(sizeof(s_node)), __FILE__, __LINE__);
    node->type = ERROR_NODE;
    node->data.error = msg;
    return (node);
}

void *node_drop(s_node *node)
{
    if (node->type == PAIR_NODE)
    {
            node_drop(node->data.pair.left);
            node_drop(node->data.pair.right);
    } else if (node->type == STR_NODE)
        free(node->data.str);
    free(node);
    return NULL;
}
