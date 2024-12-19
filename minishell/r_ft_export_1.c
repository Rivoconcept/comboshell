/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:27:25 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/19 19:24:57 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_get_export_value(t_params *params, char *name)
{
    t_export   *current;

    if (!params || !name)
        return (NULL);
    current = params->myexport;
    while (current != NULL)
    {
        if (!ft_strcmp(current->name, name))
            return (ft_strdup(current->value));
        current = current->next;
    }
    return (NULL);
}

int print_export(t_params *params)
{
    t_export *current;

    current = params->myexport;
    if (current == NULL)
        return (1);
    while (current != NULL)
    {
        if (!current->value)
           printf("declare -x %s\n", current->name); 
        else
            printf("declare -x %s=\"%s\"\n", current->name, current->value);
        current = current->next;
    }
    return (0);
}

int check_error_var_export(char *cmd)
{
    int i;
    char **argv;

    i = 0;
    if (!ft_strchr(cmd, '=') || (ft_isdigit(cmd[0]) && ft_strchr(cmd, '=')))
        return (1);
    argv = ft_split(cmd, '=');
    if (!argv)
        return (1);
    while (argv[0][i] && (ft_isalnum(argv[0][i])
        || argv[0][i] == '_'))
        i++;
    if (argv[0][i] != '\0')
    {
        free_array(argv);
        argv = NULL;
        return (1);
    }
    free_array(argv);
    return (0);
}

int check_error_export(char *cmd)
{
    int i;
    char **argv;

    i = 0;
    if (cmd[0] == '\0' || cmd[0] == '=' || ft_isdigit(cmd[0]))
        return (1);
    argv = ft_split(cmd, '=');
    if (!argv)
        return (1);
    while (argv[0][i] && (ft_isalnum(argv[0][i])
        || argv[0][i] == '_'))
        i++;
    if (argv[0][i] != '\0')
    {
        free_array(argv);
        argv = NULL;
        return (1);
    }
    free_array(argv);
    return (0);
}

int put_var_export(char **cmd, t_params *params)
{
    int i;
    char    *name;

    i = 0;
    while (cmd[i] != NULL)
        i++;
    if (i > 1 || check_error_var_export(cmd[0]))
        return (0);
    name = put_name_export(cmd[0]);
    if (!name)
        return (0);
   if (find_export_name(params->myexport, name))
        del_export_element(&params->myexport, name);
    free(name);
    create_export(&params->myexport, cmd[0]);
    return (1);
}

void    clean_export(char *exist_value, char *enter_value, char *name)
{
    if (enter_value)
        free(enter_value);
    if (exist_value)
        free(exist_value);
    if (name)
        free(name);
}

int    handle_export_1(char *arg, t_params *params)
{
    char    *name;
    char    *enter_value;
    char    *exist_value;

    exist_value = NULL;
    enter_value = NULL;
    name = put_name_export(arg);
    if (!name)
        return (0);
    exist_value = put_export_val(params->myexport, name);
    enter_value = put_value_export(arg);
    if (!ft_strchr(arg, '=') && !find_export_name(params->myexport, name))
        return (create_export(&params->myexport, arg), 
        clean_export(exist_value, enter_value, name), 1);
    if (ft_strchr(arg, '=') && !find_export_name(params->myexport, name)
        && (exist_value == NULL || !exist_value) 
        && !ft_strncmp(enter_value, "\0", 1))
        return (create_export(&params->myexport, arg), 
        clean_export(exist_value, enter_value, name), 2);
    clean_export(exist_value, enter_value, name);
    return (0); 
}

int    handle_export_2(char *arg, t_params *params)
{
    char    *name;
    char    *enter_value;
    char    *exist_value;

    exist_value = NULL;
    enter_value = NULL;
    name = put_name_export(arg);
    if (!name)
        return (0);
    exist_value = put_export_val(params->myexport, name);
    enter_value = put_value_export(arg);
    if (ft_strchr(arg, '=') && find_export_name(params->myexport, name)
        && !ft_strncmp(enter_value, "\0", 1))
       return (del_export_element(&params->myexport, name), free(enter_value),
        create_export(&params->myexport, arg),
        clean_export(exist_value, enter_value, name), 3);
    if (ft_strchr(arg, '=') && !find_export_name(params->myexport, name)
        && ft_strlen(enter_value))
       return (create_export(&params->myexport, arg), create_env(&params->myenvp, arg),
        clean_export(exist_value, enter_value, name), 4);
    clean_export(exist_value, enter_value, name);
    return (0);
}

int ft_export(char **cmd, t_params *params)
{
    int     i;

    i = 1;
    if (!cmd[1])
        return (print_export(params));
    while (cmd[i] != NULL)
    {
        if (check_error_export(cmd[i]))
            printf("minishell: export: `%s': not a valid identifier\n", 
            cmd[i]);
        else
        {
            printf("%d\n", handle_export_1(cmd[i], params));
            printf("%d\n", handle_export_2(cmd[i], params));
        }

        i++;
    }
    
    /*if (!ft_strcmp(cmd[0], "export"))
    {
        if (!cmd[1])
            print_export(params);
        else if (cmd[1][0] == '\0' || cmd[1][0] == '=')
             return (printf("minishell: export: `%s': not a valid identifier\n", 
             cmd[1]), 1);
        int i;

    if (check_error_var_temp(cmd[1]))
        return (0);
    name = put_name_export(cmd[0]);
    if (!name)
        return (0);
    enter_value = put_value_export(name);
    exit_value = ft_get_export_value(params, name);
    if (enter_value == NULL && exit_value != NULL && find_export_name(params->myexport, cmd[0]))
        return (free(name), free(exit_value), 1);
    if (exit_value != NULL && enter_value != NULL)
        if (!ft_strncmp(enter_value, exit_value, ft_strlen(enter_value)))
            del_export_element(&params->myexport, name);

    if (enter_value != NULL)
        free(enter_value);
    if (exit_value != NULL)
        free(exit_value);
    free(name);
        
        else if (!ft_strchr(cmd[1], '=') && !find_export_name(params->myexport, cmd[1]))
        {
        }
        else if (ft_strchr(cmd[1], '='))
        {

            create_env(&params->myenvp, cmd[1]);
        }
    }*/
    return (0);
}

