/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:39:54 by rhanitra          #+#    #+#             */
/*   Updated: 2024/09/26 20:33:59 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(nmemb * size);
	if (str == 0)
		return (0);
	while (i < nmemb * size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

char	*ft_strd(const char *s)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strsize((char *)s) + 1));
	if (!new_str)
		return (NULL);
	while (s[i] != '\0')
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/*char **add_argument(char **argv, int *argc, char *arg)
{
    char **new_argv;
    int i;

    i = 0;
    new_argv = ft_calloc(*argc + 2, sizeof(char *));
    if (!new_argv)
        return NULL;
    while (i < *argc)
    {
        new_argv[i] = argv[i];
        i++;
    }
    new_argv[*argc] = ft_strd(arg);
    new_argv[*argc + 1] = NULL;
    free(argv);
    (*argc)++;
    return (new_argv);
}*/

/*int check_insimplequote(const char *str, int *i, 
    int *in_double_quote, int *in_single_quote)
{
    if (str[*i] == '\'' && !in_double_quote)
    {
        in_single_quote = !in_single_quote;
        *i++;
        return (1);
    }
    return (0);
}*/

/*char **parse_command(const char *str)
{
    int     i;
    int     start;
    int     argc;
    char    **argv;
    int     in_single_quote;
    int     in_double_quote;
    char    buffer[1024];

    i = 0;
    start = 0;
    argc = 0;
    argv = NULL;
    in_single_quote = 0;
    in_double_quote = 0;  
    while (str[i] != '\0')
    {
        if (str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
            continue;
        }
        if (str[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
            continue;
        }

        // Gérer les espaces comme séparateurs quand on n'est pas entre des guillemets
        if (ft_isspace(str[i]) && !in_single_quote && !in_double_quote)
        {
            if (i > start) {
                ft_strncpy(buffer, &str[start], i - start);
                buffer[i - start] = '\0';
                argv = add_argument(argv, &argc, buffer);
            }
            i++;
            while (ft_isspace(str[i]))
                i++; // Sauter les espaces supplémentaires
            start = i;
            continue;
        }

        i++;
    }

    // Ajouter le dernier argument après la fin de la chaîne
    if (i > start)
    {
        ft_strncpy(buffer, &str[start], i - start);
        buffer[i - start] = '\0';
        argv = add_argument(argv, &argc, buffer);
    }

    return argv;
}*/

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

int put_word_len(char *str)
{
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (str[i] != '\0' && (str[i] != ' ' || in_single_quote || in_double_quote))
    {
        handle_quotes(str[i], &in_single_quote, &in_double_quote);
        i++;
    }
    return i;
}

int word_count(char *str)
{
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (str[i] != '\0')
    {
        handle_quotes(str[i], &in_single_quote, &in_double_quote);

        if (str[i] != ' ' && (i == 0 || (str[i - 1] == ' ' && !in_single_quote && !in_double_quote)))
            j++;
        i++;
    }
    return j;
}

char *split_word(char *str, int index)
{
    int i = 0;
    int size_word = put_word_len(&str[index]);
    char *temp = (char *)malloc(sizeof(char) * (size_word + 1));
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (!temp)
        return (NULL);

    while (str[index] != '\0' && (str[index] != ' ' || in_single_quote || in_double_quote))
    {
        handle_quotes(str[index], &in_single_quote, &in_double_quote);
        temp[i++] = str[index++];
    }
    temp[i] = '\0';
    return temp;
}

char **ft_splits(char const *s)
{
    int i = 0;
    int j = 0;
    char **split;

    if (!s)
        return (NULL);

    split = (char **)malloc(sizeof(char *) * (word_count((char *)s) + 1));
    if (!split)
        return (NULL);

    while (s[i] != '\0')
    {
        if (s[i] != ' ')
        {
            split[j++] = split_word((char *)s, i);
            i += put_word_len((char *)s + i);
        }
        else
            i++;
    }
    split[j] = NULL;
    return split;
}
