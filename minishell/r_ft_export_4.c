/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:27:25 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/20 19:32:04 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    exist_value = put_export_str(params->myexport, name);
    enter_value = put_value_export(arg);
    if (!find_char(arg, '=') && !find_export_name(params->myexport, name))
        return (create_export(&params->myexport, arg),  
        clean_export(exist_value, enter_value, name), 1);
    if (find_char(arg, '=') && !find_char(arg, '+'))
        return (del_export_element(&params->myexport, name),
        del_env_element(&params->myenvp, name),
        create_export(&params->myexport, arg),
        create_env(&params->myenvp, arg), 
        clean_export(exist_value, enter_value, name), 2);
    clean_export(exist_value, enter_value, name);
    return (0); 
}

int    handle_export_2(char *arg, t_params *params)
{
    char    *name;
    char    *temp;
    char    *enter_value;
    char    *exist_value;

    temp = NULL;
    exist_value = NULL;
    enter_value = NULL;
    name = put_name_export(arg);
    if (!name)
        return (0);
    exist_value = put_export_value(params->myexport, name);
    enter_value = put_value_export(arg);
     if (!find_char(arg, '+') && !find_char(arg, '=') && enter_value == NULL 
        && exist_value[0] != '\0')
    {
        temp = put_export_str(params->myexport, name);
        return (del_env_element(&params->myenvp, name),
            create_env(&params->myenvp, temp), free(temp),
        clean_export(exist_value, enter_value, name), 3);
    }       
    clean_export(exist_value, enter_value, name);
    return (0);
}   

int    handle_export_3(char *arg, t_params *params)
{
    char    *name;

    name = put_name_export(arg);
    if (!name)
        return (0);
     if (find_char(arg, '+') && find_char(arg, '=')
        && !find_export_name(params->myexport, name))
        return (del_export_element(&params->myexport, name),
            del_env_element(&params->myenvp, name),
            create_export(&params->myexport, arg),
            create_env(&params->myenvp, arg), 
            clean_export(NULL, NULL, name), 4);
    return (clean_export(NULL, NULL, name), 0);
}

int    handle_export_4(char *arg, t_params *params)
{
    char    *name;
    char    *temp;
    char    *enter_value;
    char    *concat_value;

    temp = NULL;
    enter_value = NULL;
    concat_value = NULL;
    name = put_name_export(arg);
    enter_value = put_value_export(arg);
    if (find_char(arg, '+') && find_char(arg, '=')
        && find_export_name(params->myexport, name))
    {
        temp = put_export_str(params->myexport, name);
        concat_value = ft_strjoin(temp, enter_value);
        free(temp);
        return (del_export_element(&params->myexport, name),
            del_env_element(&params->myenvp, name),
            create_export(&params->myexport, concat_value),
            create_env(&params->myenvp, concat_value), free(concat_value),
        clean_export(NULL, enter_value, name), 5);
    }
    return (clean_export(NULL, enter_value, name), 0);
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
            handle_export_1(cmd[i], params);
            handle_export_2(cmd[i], params);
            handle_export_3(cmd[i], params);
            handle_export_4(cmd[i], params);
        }
        i++;
    }
    return (0);
}

