/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:11:07 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/18 10:32:00 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int get_pos_last_slash(const char *s, char c)
{
    int i;
    int pos;

    i = 0;
    pos = -1;
    while (s[i] != '\0')
    {
        if (s[i] == c)
            pos = i;
        i++;
    }
    return (pos);
}

char *return_pdir(char *cwd)
{
    int i;
    int size;
    char *path;

    i = -1;
    size = get_pos_last_slash(cwd, '/');
    path = (char *)malloc(sizeof(char) * (size + 1));
    if (!path)
        return (NULL);
    while (++i < size)
        path[i] = cwd[i];
    path[i] = '\0';
    return (path);
}

void check_cdir(char *arg, char *cwd, char **new_path)
{
    char *tmp;

    tmp = NULL;
    if (strcmp(arg, ".") == 0)
    {
        if (*new_path)
            free(*new_path);
        *new_path = strdup(cwd);
        if (!(*new_path)) {
            printf("Error: strdup failed\n");
            return;
        }
        return;
    }
    if (arg[0] != '.' || (arg[0] == '.' && arg[1] != '/'))
    {
        *new_path = ft_strjoin(cwd, "/");
        if (!(*new_path))
            return; 
        tmp = ft_strjoin(*new_path, arg);
        free(*new_path);
        if (!tmp)
            return;
        *new_path = tmp;
    }
    if (strcmp(arg, "..") == 0)
    {
        if (*new_path)
            free(*new_path);
        *new_path = return_pdir(cwd);
        if (!*new_path)
        {
            printf("Error: strdup failed\n");
            return;
        }
    }
}

void check_punkt(char *arg, char *cwd, char **new_path)
{
    if (strcmp(arg, ".") == 0)
    {
        if (*new_path)
            free(*new_path);
        *new_path = strdup(cwd);
        if (!(*new_path)) {
            printf("Error: strdup failed\n");
            return;
        }
        return;
    }
}

char *return_path_dir(char *argv)
{
    char *new_path;
    char *cwd;

    new_path = NULL;
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        return (perror("Error on getcwd"), NULL);
    if (argv[0] == '.' && argv[1] == '/')
    {
        new_path = ft_strjoin(cwd, &argv[1]);
        if (!new_path)
            return (free(cwd), NULL);
    }
    else
    {
      //  check_punkt(argv, cwd, &new_path);
        check_cdir(argv, cwd, &new_path);
    }
    free(cwd);
    if (new_path && access(new_path, F_OK) == 0)
        return new_path;
    printf("minishell: cd: %s: No such file or directory\n", argv);
    free(new_path);
    return NULL;
}

int main(int argc, char **argv)
{
    char *path;

    path = NULL;
    if (argc == 2 && !argv[1][0])
        return (0);
    if (argc == 1)
    {
        path = getenv("HOME");
        // if (!path)
        //     return (printf("minishell: cd: HOME not set\n"), 1);

    }
    else
    {
        path = return_path_dir(argv[1]);
        if (!path)
            return (1);
    }
    if (!argv[0])
        path = ft_strdup("cd");
    if (path && chdir(path) != 0)
        perror("Error on cd");
    else
        print_prompt();
    if (argc > 1)
        free(path);
    return (0);
}