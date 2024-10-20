/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:11:13 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/12 19:34:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
    if (c == '\'' && !(*in_double_quote))
    {
        *in_single_quote = !(*in_single_quote);
    }
    if (c == '"' && !(*in_single_quote))
    {
        *in_double_quote = !(*in_double_quote);
    }
}
