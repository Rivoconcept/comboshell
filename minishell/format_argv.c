/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:26:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/25 11:47:55 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"


char *check_val_env(char *str, int *index, t_params *params)
{
    int i;
    char var_env[256];
    char *env_value;

    i = 0;
    (*index)++;
    env_value = NULL;
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
    else
        return (NULL);
}

void put_var_env(char *input, int *i, char **temp, t_params *params)
{
    if (in_double_quote(input))
        *temp = check_val_env(input, i, params);
    else if (in_single_quote(input))
    {
        if (input[*i - 1] == '\'' && *i > 1)
            *temp = check_val_env(input, i, params);
        else
            *temp = ft_strdup("$");
    }
    else if (pure_quote(input))
        *temp = check_val_env(input, i, params);
    else if (pure_apostrophe(input))
        *temp = ft_strdup("$");
    else if (!pure_quote(input) && !pure_apostrophe(input)
        && !in_double_quote(input) && !in_single_quote(input))
        *temp = check_val_env(input, i, params);
}


char *format_var_env(char *arg, t_params *params)
{
    int i[3] = {-1, 0, 0};
    char *temp;
    static char new_str[1024];

    while (arg[++i[0]] != '\0')
    {
        if (arg[i[0]] == '$')
        {
            i[2] = 0;
            temp = NULL;
            put_var_env(arg, &i[0], &temp, params);
            if (temp)
            {
                while(temp[i[2]] != '\0')
                    new_str[(i[1])++] = temp[(i[2])++];
                free(temp);
            }
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