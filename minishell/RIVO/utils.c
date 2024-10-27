/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 14:59:38 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rivo.h"

int check_input(char *s, char *base)
{
    int i;
    int j;
    int found;

    i = 0;
    while (s[i] != '\0')
    {
        j = 0;
        found = 0;
        while (base[j] != '\0')
        {
            if (s[i] == base[j])
            {
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
            return (0);
        i++;
    }
    return (1);
}

int check_str(const char *big, const char *little, char *check)
{
    size_t i;
    size_t j;
    size_t len;

    i = 0;
    j = 0;
    len = ft_strlen(little);
    if (!*little || !check_input((char *)big, check))
        return (0);
    while (big[i] != '\0' && len > 0)
    {
        j = 0;
        if (big[i] == little[j] && i != 0)
        {
            while (little[j] && j < len && big[i + j] == little[j])
                j++;
            if (little[j] == '\0')
                return (i);
        }
        i++;
    }
    return (0);
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

int	isbuiltins(char *command)
{
	int		i;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};

	i = 0;
	while (builtins[i] != NULL)
	{
		if (!ft_strcmp(command, builtins[i]) && ft_strlen(command) == ft_strlen(builtins[i]))
			return (1);
        i++;
	}
	return (0);
}

char	*check_cmd_builtins(char *command)
{
	int		i;
	char	*full_path;
    char    *path;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};

	i = 0;
    path = "./builtins/exec/";
	full_path = NULL;
	while (builtins[i] != NULL)
	{
		if (!ft_strcmp(command, builtins[i]))
        {  
            full_path = ft_strjoin(path, builtins[i]);
			if (full_path == NULL)
				return (NULL);
            break;
        }
        i++;
	}
	return (full_path);
}