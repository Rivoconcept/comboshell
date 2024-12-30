/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/30 13:43:35 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int check_pipe_out_quote(char *input, int i, char c)
{
    int j;
    int k;
    int lquote;
    int rquote;

    lquote = 0;
    rquote = 0;
    if (input[i] == c)
    {
        j = i - 1;
        k = i + 1; 
        check_left_quote(input, &j, &lquote);
        check_right_quote(input, &k, &rquote);
        if ((lquote % 2 == 0) && (rquote % 2 == 0))
            return (1);
    }
    return (0);
}

int check_echo(char *s, int *i, char *new_str, int *j)
{
    if (!s || *i < 0)
        return (0);

    if ((s[*i] == 'e' && s[*i + 1] == 'c'  
        && s[*i + 2] == 'h' && s[*i + 3] == 'o'))
    {
        new_str[(*j)++] = s[(*i)++];
        new_str[(*j)++] = s[(*i)++];
        new_str[(*j)++] = s[(*i)++];
        new_str[(*j)++] = s[(*i)++];
        while (s[*i] != '\0')
        {
			if ((s[*i] ==  '|' && check_pipe_out_quote(s, *i, '|'))
                || (s[*i] ==  '<' && check_pipe_out_quote(s, *i, '<'))
                || (s[*i] ==  '>' && check_pipe_out_quote(s, *i, '>')))
					break;
            new_str[(*j)++] = s[(*i)++];
        }
        return (1);
    }
    return (0);
}

char *format_input(char *input)
{
    int i;
    int j;
    char *new_str;

    i = 0;
	j = 0;
	if (!input)
        return (NULL);
    new_str = malloc(sizeof(char) * (put_new_size(input) + 1));
    if (!new_str)
        return (NULL);
    while (input[i])
    {
        if (check_echo(input, &i, new_str, &j))
            continue ;
        if (is_operator(input[i]))
            add_spaces(new_str, input, &i, &j);
        else
            new_str[j++] = input[i];
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}


