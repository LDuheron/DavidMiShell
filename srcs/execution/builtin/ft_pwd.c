/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbocanci <sbocanci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:30:11 by svoi              #+#    #+#             */
/*   Updated: 2023/07/22 12:01:44 by sbocanci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_cmd_lst *cmd_lst)
{
	char	*pwd;

	pwd = cmd_lst->cmd_node->argument[1];
	if (pwd && ft_strcmp(pwd, "--help") == 0)
	{
		ft_putstr_fd("pwd: pwd [OPTION]\n", 1);
		ft_putstr_fd("\tPrint the name of the current working directory.\n", 1);
		ft_putstr_fd("\n\tOptions:\n", 1);
		ft_putstr_fd("\t--help\t\tprint this help message and exit\n\n", 1);
		ft_putstr_fd("\tExit Status:\n", 1);
		ft_putstr_fd("\tReturns 0 unless an invalid option is given or\n", 1);
		ft_putstr_fd("\tthe current directory cannot be read.\n", 1);
		data->exit_code = 2;
		return (0);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		ft_putendl_fd(pwd, 1);
		free(pwd);
		data->exit_code = 0;
		return (0);
	}
}
