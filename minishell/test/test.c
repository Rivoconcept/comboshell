#include "test.h"

int in_apostrophe(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (str && str[0] == '\'' && str[i - 1] == '\'');
}

int in_quote(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (str && str[0] == '"' && str[i - 1] == '"');
}

int pure_apostrophe(char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"')
            j++;
        if (str[i] == '\'')
            k++;
        i++;
    }
    return (str && str[0] == '\'' && str[i - 1] == '\'' && j == 0 && k == 2);
}

int pure_quote(char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'')
            j++;
        if (str[i] == '"')
            k++;
        i++;
    }
    return (str && str[0] == '"' && str[i - 1] == '"' && j == 0 && k == 2);
}


void manage_quotes(char c, int *single_quote, int *double_quote)
{
    if (c == '\'' && !(*double_quote))
    {
        *single_quote = !(*single_quote);
    }
    if (c == '"' && !(*single_quote))
    {
        *double_quote = !(*double_quote);
    }
}

int in_single_quote(char *str)
{
    int i;
    int apostrophe;
    int quote;

    i = 0;
    apostrophe = 0;
    quote = 0;
    while (str[i] != '\0')
    {
        manage_quotes(str[i], &apostrophe, &quote);
        if (str[i] == '"' && apostrophe)
            return (1);
        i++;
    }
    return (0);
}


int in_double_quote(char *str)
{
    int i;
    int apostrophe;
    int quote;

    i = 0;
    apostrophe = 0;
    quote = 0;
    while (str[i] != '\0')
    {
        manage_quotes(str[i], &apostrophe, &quote);
        if (str[i] == '\'' && quote)
            return (1);
        i++;
    }
    return (0);
}

/******************************************************************/


int echap_quote(char c, int *in_single_quote, int *in_double_quote)
{
    if (c == '\'' && !(*in_double_quote) && !(*in_single_quote))
    {
        *in_single_quote = !(*in_single_quote);
        return (1);
    }
    if (c == '\'' && !(*in_double_quote) && *in_single_quote) 
    {
        *in_single_quote = !(*in_single_quote);
        return (1);
    }
    if (c == '"' && !(*in_single_quote) && !(*in_double_quote))
    {
        *in_double_quote = !(*in_double_quote);
        return (1);
    }
    if (c == '"' && !(*in_single_quote) && *in_double_quote) 
    {
        *in_double_quote = !(*in_double_quote);
        return (1);
    }
    return (0);
}

char *format_quotes(char *command)
{
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    char *new_path;

    new_path = (char *)malloc(sizeof(char) * ft_strlen(command) + 1);
    if (!new_path)
        return (NULL);
    while (command[i] != '\0')
    {
        if (echap_quote(command[i], &in_single_quote, &in_double_quote))
        {
            i++;
            continue;
        }
        new_path[j] = command[i];
        i++;
        j++;
    }
    new_path[j] = '\0';
    return (new_path);
}
/*************************************************** */

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


/********************************************************************* */

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
    int i;
    int in_single_quote;
    int in_double_quote;

    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    while (str[i] != '\0' && (str[i] != ' '
        || in_single_quote || in_double_quote))
    {
        handle_quotes(str[i], &in_single_quote, &in_double_quote);
        i++;
    }
    return (i);
}

int check_quote(char c, char *str, int *i)
{
    if (str[*i] == c)
    {
        (*i)++;
        while (str[*i] != c && str[*i] != '\0')
            (*i)++;
        if (str[*i] == c && str[*i - 1] !=  c)
        {
            (*i)++;
            return (1);
        }
    }
    return (0);
}

int word_count(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if (check_quote('\'', str, &i) || check_quote('"', str, &i))
            j++;
        else if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
        {
            j++; 
            while (str[i] != ' ' && str[i] != '\0')
                i++;
        }
        else
            i++;
    }
    return (j);
}


char *split_word(char *str, int index)
{
    int i = 0;
    char *temp;
    int in_single_quote;
    int in_double_quote;

    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    temp = (char *)malloc(sizeof(char) * (put_word_len(&str[index]) + 1));
    if (!temp)
        return (NULL);
    while (str[index] != '\0' && (str[index] != ' '
        || in_single_quote || in_double_quote))
    {
        handle_quotes(str[index], &in_single_quote, &in_double_quote);
        temp[i++] = str[index++];
    }
    temp[i] = '\0';
    return (temp);
}


char **parse_command(char const *input)
{
    int i;
    int j;
    char **split;

    if (!input)
        return (NULL);
    i = 0;
    j = 0;
    split = (char **)malloc(sizeof(char *) * (word_count((char *)input) + 1));
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


/**************************************************************** */

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
        return (ft_itoa(params->wstatus));
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


/******************************************************************* */

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

char *check_access(char *full_path, char *command, char *path)
{
    if (putchar_count(command, '/') > 1 && command[0] == '/')
        full_path = ft_strjoin(path, (strrchr(command, '/') + 1));
    else if (!putchar_count(command, '/'))
        full_path = ft_strjoin(path, command);
    free(path);
    if (!full_path)
        return (NULL);
    if ((command[0] == '/' && (putchar_count(command, '/') == 1 
        || !find_first_index(full_path, command)))
        || (command[0] != '/' && putchar_count(command, '/')))
    {
        free(full_path);
        full_path = strdup(command);
    }
    if (!full_path)
        return (NULL);
    return (full_path);
}

char *put_path(char **dirs, char *command)
{
	int		i;
	char	*path;
    char    *full_path;

    i = 0;
	path = NULL;
    full_path = NULL;
	while (dirs[i] != NULL)
	{
        path = ft_strjoin(dirs[i], "/");
    	if (!path)
			return (NULL);
        full_path = check_access(full_path, command, path);
    	if (!full_path)
			return (free(path), NULL);
        if (access(full_path, X_OK | F_OK) == 0)
            return (free(path), full_path);
        free(path);
		free(full_path);
        i++;
	}
    return (NULL);
}

char *check_cmd_standard(char *command)
{
	char	**dirs;
    char    *path_env;
	char    *full_path;

	full_path = NULL;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	full_path = put_path(dirs, command);
	free_array(dirs);
	if (!full_path)
    {
        printf("%s : command not found\n", command);
		return (ft_strdup(""));
    }
	return (full_path);
}

int token_type(char *arg)
{
    char    *temp;

    temp = format_quotes(arg);
    if (ft_strcmp(temp, "|") == 0 || ft_strcmp(temp, ">") == 0 
        || ft_strcmp(temp, "<") == 0 || ft_strcmp(temp, ">>") == 0 
        || ft_strcmp(temp, "&&") == 0 || ft_strcmp(temp, "||") == 0)
    {
        free(temp);
        return (1);
    }
    if (temp[0] == '-')
    {
        free(temp);
        return (2);
    }
    if (ft_strchr(temp, '$') == NULL)
    {
        free(temp);
        return (3);
    }
    return (free(temp), 0);
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
        if (i == 0  || token_type(argv[i]) == 1 || token_type(argv[i]) == 3
            || (token_type(argv[i]) == 2) || token_type(argv[i - 1]) == 1)
        {
            temp = format_quotes(argv[i]);
            free(argv[i]);
            argv[i] = temp;
        }
        i++;
    }
    free(new_input);
	return (argv);
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

void print_char(char *input, int *i, int fd)
{
    if (in_single_quote(input) && input[*i] != '\'')
        ft_putcharfd(input[*i], fd);
    else if (in_double_quote(input) && input[*i] != '"')
        ft_putcharfd(input[*i], fd);
    else if (pure_apostrophe(input) && input[*i] != '\'')
        ft_putcharfd(input[*i], fd);
    else if (pure_quote(input) && input[*i] != '"')
        ft_putcharfd(input[*i], fd);
    else if (!pure_apostrophe(input) && !pure_quote(input) 
        && !in_double_quote(input) && !in_single_quote(input))
        ft_putcharfd(input[*i], fd);
}

char *format_str_quotes(char *arg)
{
    int i;
    int j;
    char *temp;

    i = 0;
    j = 0;
    temp = (char *)malloc(sizeof(char) * (ft_strlen(arg) + 1));
    if (!temp)
        return (NULL);
    while (arg[i] != '\0')
    {
        if (in_single_quote(arg) && arg[i] != '\'')
            temp[j] = arg[i];
        else if (in_double_quote(arg) && arg[i] != '"')
            temp[j] = arg[i];
        else if (pure_apostrophe(arg) && arg[i] != '\'')
            temp[j] = arg[i];
        else if (pure_quote(arg) && arg[i] != '"')
            temp[j] = arg[i];
        else if (!pure_apostrophe(arg) && !pure_quote(arg) 
            && !in_double_quote(arg) && !in_single_quote(arg))
            temp[j] = arg[i];
        i++;
        j++;
    }
    temp[j] = '\0';
    return (temp);
}

void format_arg_quotes(char **argv)
{
    int i;
    char *tmp;

    i = 0;
    while(argv[i] != NULL)
    {
        tmp = format_str_quotes(argv[i]);
        free(argv[i]);
        argv[i] = tmp;
        i++;
    }
}

char	**put_argv(char **argv, char *input, t_params *params)
{
	char	*cmd;

	cmd = NULL;
	argv = format_argv(input);
    format_variable(argv, params);
    // format_arg_quotes(argv);   
	if (!isbuiltins(argv[0]))
		cmd = check_cmd_standard(argv[0]);
	else
		cmd = check_cmd_builtins(argv[0]);
	if (cmd != NULL)
	{
		free(argv[0]);
		argv[0] = ft_strdup(cmd);
        free(cmd);
		return (argv);
	}
	else
	{
		printf("%s : command not found\n", argv[0]);
		free_array(argv);
	}
	return (free(cmd), NULL);
}


int main(void)
{
    t_params *params;

    params = malloc(sizeof(t_params));
    if (!params)
        return (1);
    params->wstatus = 0;
    char *path = "\"\"''\"e\"c'h'o \
                ""''-n'n's '-l's''\
                \"comment 'faire' des '$HOME'\"\
                '\"$HOME\" est un $HOME qui va \"$HOME\"'\
                ''\"\"'pe''\"y\"' \
                \"'$HOME' est un \"$HOME\" qui va '$HOME'\"||""''w'c' -l \
                > ""''test.txt";
    char **argv = NULL;
    char **new_argv = NULL;

    new_argv = put_argv(argv, path, params);

    int i = 0;
    while(new_argv[i] != NULL)
    {
        printf("%s\n", new_argv[i]);
        i++;
    }
    char *tmp;
    printf("%s\n", tmp = format_str_quotes(new_argv[3]));
    free(tmp);
    /*i = 0;
    while(new_argv[i] != NULL)
    {
        printf("%s\n", new_argv[i]);
        i++;
    }*/

    free_array(new_argv);
    free(params);
    return 0;
}

// minishell> echo '"$HOME" est un $HOME qui va "$HOME"'$HOME''
// /home/rivoinfo est un /home/rivoinfo qui va /home/rivoinfo$HOME

