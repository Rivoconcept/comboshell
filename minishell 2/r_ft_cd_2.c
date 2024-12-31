/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_cd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:11:07 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/27 12:04:13 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_oldpwd(t_params *params)
{
	char	*cwd;
	char	*export_arg;
	char	*arg_export[3];

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error on getcwd");
		params->last_exit_code = 1;
		return ;
	}
	export_arg = ft_strjoin("OLDPWD=", cwd);
	if (!export_arg)
	{
		free(cwd);
		params->last_exit_code = 1;
		return ;
	}
	arg_export[0] = "export";
	arg_export[1] = export_arg;
	arg_export[2] = NULL;
	if (ft_export(arg_export, params) != 0)
		params->last_exit_code = 1;
	free(cwd);
	free(export_arg);
}
void	return_pwd(t_params *params)
{
	char	*cwd;
	char	*export_arg;
	char	*arg_export[3];

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error on getcwd");
		params->last_exit_code = 1;
		return ;
	}
	export_arg = ft_strjoin("PWD=", cwd);
	if (!export_arg)
	{
		free(cwd);
		params->last_exit_code = 1;
		return ;
	}
	arg_export[0] = "export";
	arg_export[1] = export_arg;
	arg_export[2] = NULL;
	if (ft_export(arg_export, params) != 0)
		params->last_exit_code = 1;
	free(cwd);
	free(export_arg);
}
int	ft_cd(const char *arg, t_params *params)
{
	int		i;
	char	new_path[256];

	i = 0;
	while (params->command->cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		params->last_exit_code = 1;
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	handle_cd(&i, (char *)arg, new_path, params);
	return_oldpwd(params);
	if (chdir(new_path) != 0)
	{
		perror("cd");
		params->last_exit_code = 1;
		return (1);
	}
	return_pwd(params);
	return (0);
}