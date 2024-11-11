/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:04:33 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/25 09:04:33 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void skip_spaces(char *input, int *i)
{
    while (input[*i] == ' ')
        (*i)++;
}

static int init_quote(char *input, int *i, int *quoted, char *quote_char)
{
    if (input[*i] == '"' || input[*i] == '\'') {
        *quote_char = input[*i];
        (*i)++;
        *quoted = 1;
        return (*i);
    }
    return (*i);
}

static int handle_escape(char *input, int *i, int *escape, int quoted, char quote_char)
{
    if (*escape) {
        *escape = 0;
    } else if (input[*i] == '\\') {
        *escape = 1;
    } else if (quoted && input[*i] == quote_char) {
        return (1);
    } else if (!quoted && (input[*i] == ' ' || input[*i] == '<' || input[*i] == '>')) {
        return (1);
    }
    return (0);
}

char *extract_word(char *input, int *i)
{
    int start;
    int quoted;
    int escape;
    char quote_char;
    char *word;

    start = 0;
    quoted = 0;
    escape = 0;
    quote_char = '\0';
    skip_spaces(input, i);
    start = init_quote(input, i, &quoted, &quote_char);
    while (input[*i]) {
        if (handle_escape(input, i, &escape, quoted, quote_char))
            break;
        (*i)++;
    }
    word = ft_strndup(&input[start], *i - start);
    if (quoted && input[*i] == quote_char)
        (*i)++;
    return (word);
}

char* extract_redirection(char *input, int *i)
{
    if (input[*i] == '>') {
        (*i)++;
        if (input[*i] == '>') {
            (*i)++;
            return ft_strdup(">>");
        }
        return ft_strdup(">");
    } else if (input[*i] == '<') {
        (*i)++;
        if (input[*i] == '<') {
            (*i)++;
            return ft_strdup("<<");
        }
        return ft_strdup("<");
    }
    return NULL;
}

static e_tokentype redirection_type (char *rdir)
{
    if (!ft_strcmp(rdir, "<<"))
        return HERE_TOKEN;
    else if (!ft_strcmp(rdir, "<"))
        return LESS_TOKEN;
    else if (!ft_strcmp(rdir, ">>"))
        return GREAT_TOKEN;
    else
        return DGREAT_TOKEN;
}

s_element *parse_cmd(char *input)
{
    int i = 0;
    s_element *element_list = NULL;
    char *redir;
    char *value;

    while (input[i]) {
        while (input[i] == ' ')
            i++;
        if (input[i] == '>' || input[i] == '<') {
            redir = extract_redirection(input, &i);
            value = extract_word(input, &i);
            element_list = add_element(element_list, value, redirection_type(redir));
            free(redir);
            free(value);
        } else if (input[i]) {
            value = extract_word(input, &i);
            element_list = add_element(element_list, value, STR_TOKEN);
            free(value);
        }
    }
    return element_list;
}