/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:26:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 14:59:24 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rivo.h"

#include <stdio.h>

int var_in_apostrophe(char *input, int i)
{
    int nbr = 0;

    if (input[i] == '$')
    {
        int j = 0;
        nbr = 0;
        while (j < i)
        {
            if (input[j] == '\'')
                nbr++;
            j++;
        }
        if (nbr % 2 != 0)
            return (1);
    }
    return 0;
}

char *check_val_env(char *str, int *index, char *env_value, t_params *params)
{
    int i;
    char var_env[256];

    i = 0;
    (*index)++;
    if (str[*index] == '0')
        return (ft_strdup("minishell"));
    else if (str[*index] == '?')
        return (ft_itoa(params->status));
    else if (ft_isdigit(str[*index]) && str[(*index) - 1] == '$')
        return (ft_strdup(""));
    while (str[*index] != '\0' && str[*index] != '"' && str[*index] != '\''
        && str[*index] != ' ' && str[*index] != '$')
        var_env[i++] = str[(*index)++];
    (*index)--;
    var_env[i] = '\0';
    env_value = getenv(var_env);
    if (env_value)
        return (ft_strdup(env_value));
    else if ((var_in_apostrophe(str, *index - ft_strlen(var_env)) 
        && !in_double_quote(str)) || in_double_quote(str))
        return (NULL);
    else
        return (*index -= ft_strlen(var_env), NULL);
}

void put_var_env(char *input, int *i, char **temp, t_params *params)
{
    char *env_value;

    env_value = NULL;
    if (in_double_quote(input))
        *temp = check_val_env(input, i, env_value, params);
    else if (in_single_quote(input))
    {
        if (input[*i - 1] == '\'' && *i > 1)
            *temp = check_val_env(input, i, env_value, params);
        else
            *temp = ft_strdup("$");
    }
    else if (var_in_apostrophe(input, *i))
        *temp = ft_strdup("$");
    else if (pure_quote(input))
        *temp = check_val_env(input, i, env_value, params);
    else if (!pure_quote(input) && !pure_apostrophe(input)
        && !in_double_quote(input) && !in_single_quote(input))
        *temp = check_val_env(input, i, env_value, params);
}

void copy_var_env(char *env, char *new_str, int *index)
{
    int i;

    i = 0;
    while (env[i] != '\0')
    {
        new_str[*index] = env[i];
        (*index)++;
        i++;
    }
    free(env);
}

char *format_var_env(char *arg, t_params *params)
{
    int i[3] = {-1, 0};
    char *temp;
    static char new_str[1024];

    while (arg[++i[0]] != '\0')
    {
        if (arg[i[0]] == '$')
        {
            temp = NULL;
            put_var_env(arg, &i[0], &temp, params);
            if (temp)
                copy_var_env(temp, new_str, &i[1]);
            else if (!in_double_quote(arg))
                new_str[(i[1])++] = '$';
        }
        else
            new_str[(i[1])++] = arg[i[0]];
        new_str[i[1]] = '\0';
    }
    return (new_str);
}

void format_variable(char **argv, t_params *params)
{
    int i;
    char *tmp;

    i = 0;
    while(argv[i] != NULL)
    {
        tmp = ft_strdup(format_var_env(argv[i], params));
        free(argv[i]);
        argv[i] = tmp;
        i++;
    }
}

void	del_quotes(char **argv)
{
	int     i;
    char    *temp;

	i = 0;
    while (argv[i] != NULL)
    {
        temp = format_quotes(argv[i]);
        free(argv[i]);
        argv[i] = temp;
        i++;
    }
}