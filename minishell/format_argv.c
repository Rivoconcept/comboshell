/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:26:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/04 13:00:17 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char    *format_str_without_quote(char *input)
{
    int     i;
    int     j;
    char    *new_input;

    i = 0;
    j = 0;
    new_input = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
    if (!new_input)
        return (NULL);
    while (input[i] != '\0')
    {
        if (input[i] == '"' || input[i] == '\'')
        {
            i++;
            continue;
        }
        new_input[j] = input[i];
		i++;
		j++;
    }
    new_input[j] = '\0';
    free(input);
    return (new_input);
}

int	put_new_size(char *input, char *operators)
{
	int	i;
	int	j;
	int	new_size;

	i = -1;
	new_size = 0;
	while (input[++i] != '\0')
	{
		j = -1;
		while (operators[++j] != '\0')
		{
			if (input[i] == operators[j])
			{
				if (input[i - 1] != ' ' && input[i - 1] != operators[j]
					&& i != 0)
					new_size++;
				if (input[i + 1] != ' ' && input[i + 1] != operators[j]
					&& input[i] != '\0')
					new_size++;
			}
		}
	}
	return (ft_strlen(input) + new_size);
}

void	add_spaces(char *new_str, char *input, char c, int var[3])
{
	int	i;

	i = 0;
	if (input[(var[0]) - 1] != 32 && var[1] > 0 && new_str[var[1] - 1] != ' ')
		new_str[(var[1])++] = ' ';
	while (input[(var[0]) + i] == c)
	{
		new_str[(var[1])++] = c;
		i++;
	}
	(var[0]) += i;
	if (input[(var[0])] != 32 && input[(var[0])] != '\0')
		new_str[(var[1])++] = ' ';
}

char	*format_input(char *input, char *operators)
{
	int		var[3] = {0, 0, 0};
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (put_new_size(input, operators)
				+ 1));
	if (!new_str)
		return (NULL);
	while (input[(var[0])] != '\0')
	{
		var[2] = -1;
		while (operators[++(var[2])] != '\0')
		{
			if (input[(var[0])] == operators[(var[2])])
			{
				add_spaces(new_str, input, operators[(var[2])], var);
				break ;
			}
		}
		new_str[(var[1])++] = input[(var[0])++];
	}
	new_str[(var[1])] = '\0';
	return (new_str);
}


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

    while (str[i] != '\0' && (str[i] != ' '
        || in_single_quote || in_double_quote))
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
        if (str[i] != ' ' && (i == 0 || (str[i - 1] == ' '
            && !in_single_quote && !in_double_quote)))
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

    while (str[index] != '\0' && (str[index] != ' '
        || in_single_quote || in_double_quote))
    {
        handle_quotes(str[index], &in_single_quote, &in_double_quote);
        if ((str[index] == '\'' && str[index + 1] == '\'')
            || (str[index] == '"' && str[index + 1] == '"'))
        {
            index++;
            continue;
        }
        temp[i++] = str[index++];
    }
    temp[i] = '\0';
    return temp;
}


char **parse_command(char const *input)
{
    int i = 0;
    int j = 0;
    char **split;
    if (!input)
        return (NULL);
    split = (char **)malloc(sizeof(char *) * (word_count((char *)input) + 2));
    if (!split)
        return (NULL);
    while (input[i] != '\0')
    {
        if (input[i] != ' ')
        {
            split[j++] = split_word((char *)input, i);
            i += put_word_len((char *)input + i);
        }
        else
            i++;
    }
    split[j] = NULL;
    return (split);
}

void free_array(char **arr)
{
    int i = 0;
    while (arr[i] != NULL)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int in_simple_quote(char *str)
{
    int size;

    size = ft_strlen(str);
    return (str && str[0] == '\'' && str[size - 1] == '\'');
}

int simple_in_double_quote(char *str)
{
    int i;
    int single_quote;
    int double_quote;

    i = 0;
    single_quote = 0;
    double_quote = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"')
            double_quote++;
        if (str[i] == '\'' && double_quote == 1)
            single_quote++;
        i++;
    }
    if (double_quote == 2 && (single_quote > 0 && single_quote % 2 == 0))
        return 1;
    return 0;
}

int double_in_simple_quote(char *str)
{
    int i;
    int double_quote;
    int simple_quote;

    i = 0;
    simple_quote = 0;
    double_quote = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'')
            simple_quote++;
        if (str[i] == '"' && simple_quote == 1)
            double_quote++;
        i++;
    }
    if (simple_quote == 2 && (double_quote > 0 && double_quote % 2 == 0))
        return 1;
    return 0;
}


char	**format_argv(char *input)
{
	int     i;
    char    **argv;
    char	*new_input;
    char    *temp;

	i = 0;
    new_input = format_input(input, "&|<>;");
	argv = parse_command(new_input);
    while (argv[i] != NULL)
    {
        if (!in_simple_quote(argv[i]) && (!simple_in_double_quote(argv[i]) 
            && !double_in_simple_quote(argv[i])))
        {
            temp = format_str_without_quote(argv[i]);
            argv[i] = temp;
        }
        i++;
    }
    free(new_input);
	return (argv);
}

int main(void)
{
    // char *str = """'     ''comment \"faire\" des \"choses\" à la \"fois\"'";
    // printf("%d\n", only_quote_and_space(str, 1));
    char **argv;
    //int count;
   // int flag[2] = {0, 0};  // flag[0] = arg non `-n` trouvé, flag[1] = `-n` activé
    //char *str1 = "ech'o' -n'n''n' "    "'     ''comment \"faire\" des \"choses\" à la \"fois\"'";
    char *str2 = "echo '$HOME' \"'$HOME'\" '\"$HOME\"'";

    //(void)argc;  // Ignorer l'argument argc
    argv = format_argv(str2);
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }
    free_array(argv);
    return (0);
}*/
