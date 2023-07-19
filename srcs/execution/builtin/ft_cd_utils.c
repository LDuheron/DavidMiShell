/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svoi <svoi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:34:30 by sbocanci          #+#    #+#             */
/*   Updated: 2023/07/20 00:21:20 by svoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	settings_cd(t_cmd_lst *cmd_lst)
{
	if (cmd_lst->cmd_node->argument[1] == NULL)
		return (0);
	return (1);
}

bool	too_many_arguments(t_data *data, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->cmd_node->argument[i])
		i++;
	if (i > 2)
	{
		data->exit_code = 1;
		ft_putendl_fd("DavidMishell: cd: too many arguments", 2);
		return (true);
	}
	return (false);
}
