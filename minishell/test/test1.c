#include "test.h"

char *check_valeur_env(char *str, int *i, t_params *params)
{
    int k;
    int j;
    char var_env[256];
    char *env_value;

    k = 0;
    j = (*i) + 1;
    env_value = NULL;
    if (str[(*i) + j] == '0')
        return (ft_strdup("minishell"));
    else if (str[(*i) + j] == '?')
        return (ft_itoa(params->wstatus));
    else if (ft_isdigit(str[(*i) + j]) && str[((*i) + j) - 1] == '$')
        return (ft_strdup(""));
    while (str[(*i) + j] != '\0' && str[(*i) + j] != '"' && str[(*i) + j] != '\''
        && str[(*i) + j] != ' ' && str[(*i) + j] != '$')
        var_env[k++] = str[(*i) + j++];
    var_env[k] = '\0';
    env_value = getenv(var_env);
    if (env_value)
        return (ft_strdup(env_value));
    else
        return (NULL);
}

void put_variable_env(char *input, int *i, char **temp, t_params *params)
{
    if (in_double_quote(input))
        *temp = check_valeur_env(input, i, params);
    else if (in_single_quote(input))
    {
        if (input[*i - 1] == '\'' && *i > 1)
            *temp = check_valeur_env(input, i, params);
        else
            *temp = ft_strdup("$");
    }
    else if (pure_quote(input))
        *temp = check_valeur_env(input, i, params);
    else if (!pure_quote(input) && !pure_apostrophe(input)
        && !in_double_quote(input) && !in_single_quote(input))
        *temp = check_valeur_env(input, i, params);
}


char *format_variable_env(char *arg, t_params *params)
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
            put_variable_env(arg, &i[0], &temp, params);
            if (temp && getenv(temp) != NULL)
            {
                while(temp[i[2]] != '\0')
                    new_str[(i[1])++] = temp[(i[2])++];
                free(temp);
                i[0] = ft_strlen()
            }
        }
        else
            new_str[(i[1])++] = arg[i[0]];
        new_str[i[1]] = '\0';
    }
    return (new_str);
}


/******************************************************************* */