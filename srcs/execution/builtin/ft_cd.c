/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduheron <lduheron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:34:30 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/12 18:08:26 by lduheron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	settings_cd(t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument[1] == NULL)
		return (0);
	return (1);
}

void	ft_cd(t_data *data, t_cmd_lst *cmd_lst)
{
	char	*path;

	if (settings_cd(cmd_lst) == 0)
		path = getenv("HOME");
	else
		path = cmd_lst->cmd_node->argument[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		data->exit_code = 1;
	}
	else
	{
		data->exit_code = 0;
		change_pwd(data->m_envp, "PWD=");
		change_pwd(data->m_envp, "OLDPWD=");
	}
}
